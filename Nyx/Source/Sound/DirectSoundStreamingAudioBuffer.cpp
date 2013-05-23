/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Sound/WaveReader.h"
#include "DirectSoundStreamingAudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStreamingAudioBuffer::DirectSoundStreamingAudioBuffer(
		const AudioBufferDesc& bufferDesc, 
		const DirectSoundPtr dsound, const std::wstring& fileName)
		: DirectSoundStereoAudioBuffer(), waveReader_(new WaveReader(fileName)), bufferDesc_(bufferDesc), offset_(0){

			//�o�b�t�@���쐬

			bufferDesc_.waveFormat = waveReader_->ReadHeader();

			//�o�b�t�@�ɍĐ��f�[�^����������
			const ulong samplingRate = bufferDesc_.waveFormat.formatChunk.samplingRate;   
			const ulong blockAlign   = bufferDesc_.waveFormat.formatChunk.blockSize;  
			const ulong size         = samplingRate * 2 * blockAlign / NotifyEventNum;   
			notifySize_  = size;

			Load(bufferDesc_, dsound);
			WriteWaveData();

			//�ʒm�X���b�h�̐���
			notifyThreadHandle_ = CreateThread( NULL,0, NotifyProc, (void*)this, 0, 0);

			//�ʒm�C�x���g�̐ݒ�
			LPDIRECTSOUNDNOTIFY notify;
			DSBPOSITIONNOTIFY  positionNotify[NotifyEventNum] = {};
			HRESULT hr = GetHandle()->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
			if ( FAILED(hr)) {
				DebugOutput::Trace("IDirectSoundNotify�̎擾�Ɏ��s���܂����B", hr);
				throw COMException("IDirectSoundNotify�̎擾�Ɏ��s���܂����B", hr);
			}

			// �C�x���g�ƃV�O�i���ɂȂ�ʒu���擾
			for( int i = 0 ; i < NotifyEventNum ; i++ ) {
				notifyEventList_[i] = CreateEvent(NULL, false, false, NULL);
				positionNotify[i].dwOffset     = (notifySize_ * i) + notifySize_-1; 
				positionNotify[i].hEventNotify = notifyEventList_[i];
			}

			// �C�x���g���Z�b�g
			hr = notify->SetNotificationPositions(NotifyEventNum, positionNotify);
			if( FAILED(hr)) {
				DebugOutput::Trace("IDirectSoundNotify�ʒm�C�x���g�̐ݒ肪���s���܂����B", hr);
				throw COMException("IDirectSoundNotify�ʒm�C�x���g�̐ݒ肪���s���܂����B", hr);
			}

			SafeRelease(notify);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStreamingAudioBuffer::~DirectSoundStreamingAudioBuffer() {
		for (auto var : notifyEventList_) {
			CloseHandle(var);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStreamingAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_StreamingAudioBuffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::WriteWaveData(){
		const auto handle = GetHandle();
		const auto size   = bufferDesc_.waveFormat.dataChunk.chunkSize;
		
		if (size <= offset_ + notifySize_) {
			offset_ = 0;
			waveReader_->SetCursor(0);
		}

		//�o�b�t�@�����b�N
		void* readData1 = nullptr;
		void* readData2 = nullptr;
		ulong readSize1  = 0;
		ulong readSize2  = 0;
		HRESULT hr = handle->Lock(0, notifySize_, &readData1, &readSize1, &readData2, &readSize2, DSBLOCK_FROMWRITECURSOR);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}

		//�o�b�t�@�ɏ�������
		ulong readBytes;
		const auto buffer = waveReader_->Read(readSize1, &readBytes);
		CopyMemory(readData1, buffer.get(), readBytes);
		offset_ += readSize1;
		if (readData2 != nullptr) {
			const auto buffer = waveReader_->Read(readSize2, &readBytes);
			CopyMemory(readData2, buffer.get(), readBytes);
			offset_ += readSize2;
		}
		
		//�o�b�t�@���A�����b�N
		hr = handle->Unlock(readData1, readSize1, readData2, readSize2);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		//�t���O�̐ݒ�
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;

		//�t�H�[�J�X���[�h�̐ݒ�
		if ( bufferDesc_.focusType == AudioUtility::FocusType_GlobalFocus) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDesc�̃Z�b�g�A�b�v
		ZeroMemory(dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc->lpwfxFormat     = &wfx;
		dsBufferDesc->dwBufferBytes   = notifySize_ * NotifyEventNum;
		dsBufferDesc->dwFlags         = flag;
		dsBufferDesc->dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc->guid3DAlgorithm = bufferDesc_.algorithm;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong _stdcall NotifyProc(void* parameter) {
		Assert(parameter != nullptr)
			auto audio = reinterpret_cast<DirectSoundStreamingAudioBuffer*>(parameter);
		audio->NotifyThread();
		return 0L;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::NotifyThread() {
		bool isDone = false;
		while( !isDone ) { 
			ulong signal = MsgWaitForMultipleObjects(NotifyEventNum, notifyEventList_, 
				FALSE, INFINITE, QS_ALLEVENTS );

			switch( signal ) {
			case WAIT_OBJECT_0: 
			case WAIT_OBJECT_0+1:
			case WAIT_OBJECT_0+2:
			case WAIT_OBJECT_0+3:
				WriteWaveData();
				break;
			case WAIT_OBJECT_0+NotifyEventNum:
				MSG msg;
				while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
					if( msg.message == WM_QUIT ){
						isDone=true;
					}
				}
				break;
			}
		}
	}
}