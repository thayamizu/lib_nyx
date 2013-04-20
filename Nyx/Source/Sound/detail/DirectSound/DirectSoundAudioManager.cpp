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
#include "IO/PackedFile.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSound3DAudioBuffer.h"
#include "DirectSound3DStreamingAudioBuffer.h"
#include "DirectSoundAudioManager.h"
#include "DirectSoundStreamingAudioBuffer.h"

namespace Nyx {
	using Nyx::PackedFile;

	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::DirectSoundAudioManager(HWND hwnd, int volume) 
		:hWnd(hwnd)
	{


		HRESULT hr = DirectSoundCreate8(NULL,&dsound,NULL);
		Assert(hr == DS_OK);
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSound�̏������Ɏ��s���܂���");
		}
		dsound->AddRef();
		// �������x���̐ݒ�
		dsound->SetCooperativeLevel(hwnd,DSSCL_EXCLUSIVE);

		SetMasterVolume(volume);

	}
	
	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::~DirectSoundAudioManager() {
		SafeRelease(dsound);
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Play(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Play();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::PlayAll() {

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Play();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Stop(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Stop();


	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::StopAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Stop();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Resume(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Resume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::ResumeAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Resume();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Reset(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Reset();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::ResetAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Reset();
			++it;
		}
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetPause(size_t index, bool p) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->SetPause(p);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetPauseAll(bool p) {

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetPause(p);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int DirectSoundAudioManager::GetMasterVolume() const {
		return masterVolume;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetMasterVolume(int v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}
		masterVolume = v;

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetVolume(v);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::GetAudioBuffer(size_t index) {
		if (index >= audioBufferList.size()) return NULL;

		return audioBufferList[index];
	}
	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::Load(const std::wstring fileName, SoundBufferType::enum_t bufferType, size_t& index) {

		//�Ō��.�����������ꏊ��(�t�@�C������.���܂܂�Ă���ꍇ�̑΍�)
		int pos = fileName.find_last_of (L".");
		if (pos == std::wstring::npos) {
			return false;//�󕶎���Ԃ�
		}
		//�g���q�݂̂��擾����
		std::wstring ext = fileName.substr(pos+1, fileName.size());

		//���[�h
		std::shared_ptr<IAudioBuffer> buffer = nullptr;
		if (ext == L"wav" || ext == L"wave") {
			buffer = LoadFromWaveFile(fileName, bufferType, index);
		}
		else if (ext == L"ogg") {
			//���Ή������A�����I�ɓ�������̂ŁA�Ƃ肠�����m�ۂ��Ă���
		}

		return buffer;
	}	

	

	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::LoadFromWaveFile(const std::wstring fileName, SoundBufferType::enum_t bufferType, size_t& index){
		std::shared_ptr<IAudioBuffer> audio = nullptr;
		switch(bufferType)
		{
		case SoundBufferType::Static:
			audio=std::make_shared<DirectSoundAudioBuffer>(dsound, fileName);
			break;
		case SoundBufferType::Static3D:
			audio=std::make_shared<DirectSound3DAudioBuffer>(dsound, fileName);
			break;
		case SoundBufferType::Streaming:
			audio=std::make_shared<DirectSoundStreamingAudioBuffer>(dsound, fileName);
			break;
		case SoundBufferType::Streaming3D:
			audio= std::make_shared<DirectSound3DStreamingAudioBuffer>(dsound, fileName);
			break;
		default:
			DebugOutput::DebugMessage("�������s");
			return nullptr;
		}

		if (audio != nullptr) {
			audio->SetVolume(GetMasterVolume());
			index = audioBufferList.size();
			audioBufferList.push_back(audio);
		}

		return audio;
	}
}