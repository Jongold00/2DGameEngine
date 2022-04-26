#include "SoundManager.hpp"

/**
 * @brief returns instance of SoundManager
 *
 * @return SoundManager
 */
SoundManager &SoundManager::getInstance()
{
  static SoundManager *instance = new SoundManager();
  return *instance;
}

/**
 * @brief acts as a constructor for SoundManager
 */
void SoundManager::startUp()
{

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  this->music = ResourceManager::getInstance().getMusic("music.wav");
  this->playerJumpSFX = ResourceManager::getInstance().getSoundEffect("jump.wav");

  this->sfx.insert(make_pair(0, "jump.wav")); // saves the sound effect for easy calling

  this->crunchSFX = ResourceManager::getInstance().getSoundEffect("crunch.wav");

  this->sfx.insert(make_pair(1, "crunch.wav"));
  this->sfx.insert(make_pair(2, "gameWon.wav"));
  this->sfx.insert(make_pair(3, "defeat.wav"));



  Mix_VolumeMusic(MIX_MAX_VOLUME/10); // lowers the volume of the music
  Mix_PlayMusic(music,-1);

}

/**
 * @brief shuts down the SoundManager
 *
 */
void SoundManager::shutDown()
{

  Mix_VolumeMusic(0);
  //Mix_PlayMusic(this->music, -1);
}

/**
 * @brief resets the sound
 * 
 */
void SoundManager::reset()
{

  Mix_VolumeMusic(MIX_MAX_VOLUME/10); // lowers the volume of the music
  Mix_PlayMusic(music,-1);
}


// plays a sound effect by index, index 0 is a jump
void SoundManager::playSoundEffect(int i)
{
    auto it = sfx.find(i);

    
    if (it == sfx.end()) {
      std::cout << "error: sound effect not found" << std::endl;
    }

    else {
      
      Mix_Chunk * effect = ResourceManager::getInstance().getSoundEffect(it->second);
      Mix_PlayChannel(-1, effect, 0);
    }

}

