#include "SoundManager.hpp"

/**
 * @file SoundManager.cpp
 * @brief Generates and plays sound effects
 */

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
  Mix_PlayMusic(music,-1);

}

void SoundManager::addSFX(std::string path) 
{
  this->sfx.insert(make_pair(sfx.size(), path));
}

void SoundManager::changeMusic(std::string path) 
{
  this->music = ResourceManager::getInstance().getMusic(path);
  Mix_PlayMusic(music,-1);

}

/**
 * @brief shuts down the SoundManager
 *
 */
void SoundManager::shutDown()
{

}

void SoundManager::reset()
{
  
}

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

