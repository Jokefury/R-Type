#include "FmodSoundManager.h"
#include "InitializeError.h"
#include <algorithm>

static void	predDestroySound(std::pair<SoundType::eSound, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> > it)
{
  FMOD_Sound_Release(it.second.first);
}

SoundManager::SoundManager()
	: system_(0)
{
	if (FMOD_System_Create(&(this->system_)) != FMOD_OK)
		throw InitializeError("FMOD cannot create.");
	if (FMOD_System_Init(this->system_, 32, FMOD_INIT_NORMAL, NULL) != FMOD_OK)
		throw InitializeError("FMOD cannot create.");
	this->loadSound("../Client/assets/music.mp3", SoundType::MUSIC_LVL1);
	this->loadSound("../Client/assets/laser.mp3", SoundType::SHOT);
	this->loadSound("../Client/assets/destroy.mp3", SoundType::DESTROY);
	this->loadSound("../Client/assets/music_boss.mp3", SoundType::MUSIC_BOSS);
}

SoundManager::~SoundManager()
{
	std::for_each(this->soundMap_.begin(), this->soundMap_.end(), predDestroySound);
	FMOD_System_Close(this->system_);
	FMOD_System_Release(this->system_);
}

void SoundManager::loadSound(std::string const &filename, SoundType::eSound type)
{
	if (this->soundMap_.find(type) != this->soundMap_.end())
		return ;
	FMOD_System_CreateSound(this->system_,
      filename.c_str(),
      FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
      0, &(this->soundMap_[type].first));
}

void SoundManager::playSound(SoundType::eSound type)
{
	if (this->soundMap_.find(type) == this->soundMap_.end())
		return ;
	FMOD_System_PlaySound(this->system_, FMOD_CHANNEL_FREE, this->soundMap_[type].first, 0, &(this->soundMap_[type].second));
	if (type == SoundType::SHOT)
	  FMOD_Channel_SetVolume(this->soundMap_[type].second, 0.5f);
	else
	  FMOD_Channel_SetVolume(this->soundMap_[type].second, 2.5f);
}

void SoundManager::playMusic(SoundType::eSound type)
{
	if (this->soundMap_.find(type) == this->soundMap_.end())
		return ;
	int	play = 0;
	FMOD_Channel_IsPlaying(this->soundMap_[type].second, &play);
	if (!play)
	{
		FMOD_System_PlaySound(this->system_, FMOD_CHANNEL_FREE, this->soundMap_[type].first, 0, &(this->soundMap_[type].second));
		FMOD_Channel_SetMode(this->soundMap_[type].second, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(this->soundMap_[type].second, 0.5f);
	}
}

void SoundManager::stop(SoundType::eSound type)
{
	if (this->soundMap_.find(type) == this->soundMap_.end())
		return ;
	FMOD_Channel_Stop(this->soundMap_[type].second);
}
