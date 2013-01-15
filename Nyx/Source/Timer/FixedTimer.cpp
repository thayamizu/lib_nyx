/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Timer/ITimer.h"
#include "Timer/Timer.h"
#include "Timer/FixedTimer.h"
namespace Nyx {
	
	//---------------------------------------------------------------------------------------
	struct FixedTimer::PImpl
	{
		PImpl()
			:timer(new Timer()), flushTime(0)
		{

		}
		std::unique_ptr<Timer> timer;///< タイマ 
		ulong flushTime;///< 前回フラッシュした時刻
	};

	//---------------------------------------------------------------------------------------
	FixedTimer::FixedTimer():
		pimpl_(new PImpl())
	{
		//タイマ生成時の時間を記憶させておく．
		//以降は、Flushを呼び出さない限りGetで常に最後にFlushした時間と同じ時間が得られる
		Flush();
	}
	
	//---------------------------------------------------------------------------------------
	FixedTimer::~FixedTimer () {
	}
	
	//---------------------------------------------------------------------------------------
	void FixedTimer::Reset() {
		pimpl_->timer->Reset();
	}
	
	//---------------------------------------------------------------------------------------
	ulong FixedTimer::Get() {
		return pimpl_->flushTime;
	}
	
	//---------------------------------------------------------------------------------------
	void FixedTimer::Set(ulong t) {
		pimpl_->timer->Set(t);
	}
	
	//---------------------------------------------------------------------------------------
	void FixedTimer::Pause(bool pause) {
		pimpl_->timer->Pause(pause);
	}
	
	//---------------------------------------------------------------------------------------
	bool FixedTimer::IsPause() {
		return pimpl_->timer->IsPause();
	}
	
	//---------------------------------------------------------------------------------------
	void FixedTimer::Restart() {
		pimpl_->timer->Restart();
	}

	//---------------------------------------------------------------------------------------
	void FixedTimer::Flush() {
		pimpl_->flushTime = pimpl_->timer->Get();
	}
}