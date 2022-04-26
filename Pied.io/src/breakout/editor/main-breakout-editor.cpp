#include "base/SDLGraphicsProgram.hpp"
#include "../BlockManager.hpp"
#include "../BreakoutUIComponent.hpp"
#include "../Paddle.hpp"
#include "../VerticalEdgeRectangle.hpp"
#include "../HorizontalEdgeRectangle.hpp"
#include "../Ball.hpp"
#include "BreakoutEditorInput.hpp"
#include <filesystem>

/**
 * @file main.c 
 * @brief This is the main file of the project.
 * 
 * \mainpage Description
 * This is a breakout project. It was made by Ishani Kapoor, 
 * Jon Gold, Elena Kosowski, and Bruno Bernardo. 
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
  string resPath = "breakout/";
  SoundManager::getInstance().addSFX(resPath + "bone_block.wav");
  SoundManager::getInstance().changeMusic(resPath + "ThroughFireAndFlames.wav");

}

int main(int argc, char **argv)
{
  std::shared_ptr<Level> level = std::make_shared<Level>(900, 600);
  // Create an instance of an object for a SDLGraphicsProgram
  SDLGraphicsProgram mySDLGraphicsProgram(level, true);

  setupBreakoutSoundManager();


  
  string levels_dir = "./res/breakout/levels/";
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

  std::cout << "Right Click to delete block. \nLeft Click to place a block\nS - Save to new\n" << std::endl;

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

  BlockManager::getInstance().loadLevelFromPath(pathToLoad, level);

  level->addObject(std::make_shared<BreakoutEditorInputManager>());


  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}










  

