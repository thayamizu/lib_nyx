#include "PCH/PCH.h"
#include "Movie/MoviePlayer.h"

namespace Nyx 
{
	//-----------------------------------------------------------------------------------
	MoviePlayer::MoviePlayer() 
	{
	}

	//-----------------------------------------------------------------------------------
	MoviePlayer::MoviePlayer(const std::wstring & name)
	{
		name;
	}

	//-----------------------------------------------------------------------------------
	MoviePlayer::~MoviePlayer()
	{
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Open(const std::wstring& name)
	{
		name;
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Close()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Play()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Stop()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Pause()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Resume()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::IsPause()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::IsPlaying()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::IsOpened()
	{
		return false;
	}
};