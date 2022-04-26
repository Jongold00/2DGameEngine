#include "base/SDLGraphicsProgram.hpp"
#include "PiedPlayer.hpp"
#include "Camera.hpp"
#include "PiedEnemy.hpp"
#include "PiedCollectible.hpp"
#include "base/SpawningComponent.hpp"
#include "UI/PiedExpTab.hpp"
#include "PiedGameStateManager.hpp"
#include "PiedBoss.hpp"
#include "PiedUIComponent.hpp"


/**
 * @file main.c 
 * @brief This is the main file of the project.
 * 
 * \mainpage Description
 * This is a breakout project. It was made by Ishani Kapoor, 
 * Jon Gold, Elena Kosowski, and Alexander Chen. 
 * 
 * \section library_sec Resources Used in Project
 * \subsection library1 Resource Manager: cs4850-lab-resources
 * Orginally adapted from the lab designed by Michael D. Shah. http://www.mshah.io/
 * \subsection library2 TinyMath: cs4850-lab-math
 * Orginally adapted from the lab designed by Michael D. Shah. http://www.mshah.io/
 * \subsection library3 SDL Graphics Implementation: cs4850-lab-setup
 * Orginally adapted from the lab designed by Michael D. Shah. http://www.mshah.io/
 * \subsection library4 Framerate: cs4850-lab-framerate
 * Orginally adapted from the lab designed by Michael D. Shah. http://www.mshah.io/
 */

void setupBreakoutSoundManager() 
{
  SoundManager::getInstance().startUp();
  string resPath = "pied/";
  SoundManager::getInstance().addSFX(resPath + "chiptune fire.wav"); //shooting sfx 0
  SoundManager::getInstance().addSFX(resPath + "8bit death.wav"); //enemy/collectable death sfx 1
  SoundManager::getInstance().addSFX(resPath + "chiptune win.wav"); //win sfx 2
  SoundManager::getInstance().addSFX(resPath + "chiptune death.wav"); //lose sfx 3
  SoundManager::getInstance().addSFX(resPath + "happy blip.wav"); //upgrade sfx 4
  
  SoundManager::getInstance().changeMusic(resPath + "arcade loop.wav"); //background music X

}

int main(int argc, char **argv)
{
  std::shared_ptr<Level> level = std::make_shared<Level>(2000, 2000);
  // Create an instance of an object for a SDLGraphicsProgram

  SDLGraphicsProgram mySDLGraphicsProgram(level, 900, 600);

  setupBreakoutSoundManager();

  shared_ptr<PiedPlayer> player = make_shared<PiedPlayer>(level->w() / 2, level->h() / 2, 50, 50);
  level->addObject(player);
  weak_ptr<PiedPlayer> pl = player;

  shared_ptr<GameObject> camera = make_shared<Camera>(0, 0, 900, 600, player);
  level->addObject(camera);


  level->addObject(make_shared<PiedCollectible>(200, 314, 50, 50));


  //level->addObject(make_shared<PiedEnemy>(level->w() / 3, level->h() / 3, 50, 50, pl));
  level->addObject(make_shared<SpawningParent>(pl));

  level->addObject(make_shared<PiedExpTab>(0, level->h() - 200, 300, 200, player->getExpScript()));
  level->addObject(std::make_shared<PiedUIManager>()); 


  level->addObject(make_shared<PiedBoss>(level->w() / 3, level->h() / 3, 100, 100)); 

  PiedGameStateManager::getInstance().startUp();

  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}










  

