#include "base/SDLGraphicsProgram.hpp"
#include "../LevelLoader.hpp"
#include "../PlatformerUIComponent.hpp"
#include "PlatformerEditorInput.hpp"
#include <filesystem>
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


void setupPlatformerSoundManager() 
{
  SoundManager::getInstance().startUp();
  string resPath = "platformer/";
  SoundManager::getInstance().addSFX(resPath + "jump.wav");
  SoundManager::getInstance().addSFX(resPath + "crunch.wav");
  SoundManager::getInstance().addSFX(resPath + "gameWon.wav");
  SoundManager::getInstance().addSFX(resPath + "defeat.wav");

  SoundManager::getInstance().changeMusic(resPath + "music.wav");

}

int main(int argc, char **argv)
{
  std::shared_ptr<Level> level = std::make_shared<Level>(900, 600);
  // Create an instance of an object for a SDLGraphicsProgram
  SDLGraphicsProgram mySDLGraphicsProgram(level, true);


  string levels_dir = "./res/platformer/levels/";
  vector<string> levels;
  set<string> sorted;

  for (auto & entry : std::filesystem::directory_iterator(levels_dir))
  {
    sorted.insert(entry.path().string());
  }

  for (auto & entry : sorted)
  {

    levels.push_back(entry);
  }

  std::cout << "Right Click to delete. \nLeft Click and hold a number to add an object.\nHold 1 - Drop a player\n" <<
  "Hold 2 - Drop a block\nHold 3 - Drop a flag\nHold 4 - Drop a collectable\nHold 5 - Drop an enemy\nS - Save to new\n" << std::endl;

  std::cout << "SELECT A LEVEL TO EDIT" << std::endl;
  std::cout << std::endl;

  for (string curr : levels)
  {
    std::cout << curr << std::endl;
  }

  string pathToLoad;
  getline(cin, pathToLoad);
  std::cout<<pathToLoad<<std::endl;
  bool validPath = find(levels.begin(), levels.end(), pathToLoad) != levels.end();
  while (!validPath) {
    std::cout << "INVALID LEVEL, SELECT AGAIN" << std::endl;
    std::cout << std::endl;

    for (string curr : levels)
    {
      std::cout << curr << std::endl;
    }
    getline(cin, pathToLoad);
    validPath = find(levels.begin(), levels.end(), pathToLoad) != levels.end();

  }

  std::cout<<pathToLoad<<std::endl;

  LevelLoader::loadLevelFromPath(pathToLoad, level);
  setupPlatformerSoundManager();
  level->addObject(std::make_shared<PlatformerEditorInputManager>());

  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}




  

