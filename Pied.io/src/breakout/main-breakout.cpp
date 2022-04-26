#include "base/SDLGraphicsProgram.hpp"
#include "BlockManager.hpp"
#include "BreakoutUIComponent.hpp"
#include "Paddle.hpp"
#include "VerticalEdgeRectangle.hpp"
#include "HorizontalEdgeRectangle.hpp"
#include "Ball.hpp"
#include "BreakoutGameStateManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"


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
  string resPath = "breakout/";
  SoundManager::getInstance().addSFX(resPath + "bone_block.wav");
  SoundManager::getInstance().changeMusic(resPath + "ThroughFireAndFlames.wav");

}       

int main(int argc, char **argv)
{
  std::shared_ptr<Level> level = std::make_shared<Level>(900, 600);
  // Create an instance of an object for a SDLGraphicsProgram
  SDLGraphicsProgram mySDLGraphicsProgram(level, false);

  setupBreakoutSoundManager();

  BlockManager::getInstance().loadLevelFromPath("./res/breakout/levels/level1.txt", level);

  level->addObject(std::make_shared<Paddle>(level->w() / 2, level->h() * (7.0/8.0), level->w() / 8, level->h() / 30));
  level->addObject(std::make_shared<Ball>(level->w() / 2, level->h() / 2));
  level->addObject(std::make_shared<VerticalEdgeRectangle>(level->w(), 0, 1, level->h()));    // Right Edge at point (w, 0), w = 1 and h = level->h()
  level->addObject(std::make_shared<VerticalEdgeRectangle>(-1, 0, 1, level->h()));            // Left Edge at point (-1, 0), w = 1 and h = level->h()
  level->addObject(std::make_shared<HorizontalEdgeRectangle>(0, -1, level->w(), 1));          // Top Edge at point (0, -1), w = level->w() and h = 1
  level->addObject(std::make_shared<BreakoutUIManager>());  


  BreakoutGameStateManager::getInstance().startUp();

  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}










  

