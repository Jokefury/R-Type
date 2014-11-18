#pragma once

#include <string>

namespace SoundType
{
	enum eSound
	{
		MUSIC_LVL1,
		MUSIC_BOSS,
		SHOT,
		DESTROY
	};
}

class ISoundManager
{
public :

	/*
	** Destroy all the allocated sound here
	*/
	virtual ~ISoundManager() {}

	virtual void playSound(SoundType::eSound type) = 0;
	virtual void playMusic(SoundType::eSound type) = 0;
	virtual void stop(SoundType::eSound type) = 0;
};