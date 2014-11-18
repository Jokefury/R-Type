#pragma once

#include "ISoundManager.h"
#include <map>
#include <fmod.h>

class SoundManager : public ISoundManager
{
	FMOD_SYSTEM*			system_;
	std::map<SoundType::eSound, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> > soundMap_;

private :
	virtual void loadSound(std::string const &filename, SoundType::eSound type);

public :
	SoundManager();
	~SoundManager();
	virtual void playSound(SoundType::eSound type);
	virtual void playMusic(SoundType::eSound type);
	virtual void stop(SoundType::eSound type);
};