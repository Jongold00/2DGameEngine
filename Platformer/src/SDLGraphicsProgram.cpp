// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "SDLGraphicsProgram.hpp"
#include <SDL.h>
#include "ResourceManager.hpp"
#include "LevelLoader.hpp"
#include <Player.hpp>
#include "Goal.hpp"
#include "Collectable.hpp"
#include "Enemy.hpp"
#include "GameStateManager.hpp"
#include "base/GameWon.hpp"
#include "TinyMath.hpp"
#include <deque>
#include <cassert>
#include <numeric>
#include <iomanip>
#include <typeinfo>
#include <iostream>
#include <set>

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);

// language check boolean
bool langCheck;
// Player *player;

/**
 * @brief Construct a new SDLGraphicsProgram::SDLGraphicsProgram object
 * Returns a true or false value based on successful completion of setup.
 * @param w, type int, width of the window
 * @param h, type int, height of window
 */
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h, bool em) : screenHeight(h), screenWidth(w), editorMode(em)
{
  // Initialize random number generation.
  srand(time(NULL));
  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = NULL;
  // Render flag

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
    success = false;
  }

  else
  {
    // Create window
    gWindow = SDL_CreateWindow("Platformer", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    // Check if Window did not create.
    if (gWindow == NULL)
    {
      errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }

    // Create a Renderer to draw on
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if (gRenderer == NULL)
    {
      errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }
  }

  ResourceManager::getInstance().startUp(gRenderer);
  // If initialization did not work, then print out a list of errors in the constructor.
  if (!success)
  {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  }
  else
  {
    std::cout << "No SDL errors Detected in during init\n\n";
  }

  SoundManager::getInstance().startUp();
  // If initialization did not work, then print out a list of errors in the constructor.
  if (!success)
  {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  }
  else
  {
    std::cout << "No SDL errors Detected in during init of SoundManager\n\n";
  }

  string levels_dir = "./res/levels/";
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

  
  LevelLoader::level_paths = levels;
  LevelLoader::w = w;
  LevelLoader::h = h;
  LevelLoader::renderer = gRenderer;

  std::cout << "D - Enter Deletion / Creation mode \nC - Exit Deletion / Creation mode\nClick to delete. Click and hold a number to add an object.\nHold 0 - Drop a player\n" <<
  "Hold 1 - Drop a block\nHold 2 - Drop a flag\nHold 3 - Drop a collectable\nHold 4 - Drop an enemy\nS - Save to new\n" << std::endl;

  if (editorMode) {
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
    currentLevel = LevelLoader::loadLevelFromPath(pathToLoad);
    currentLevel->update(editorMode);


  }

  else {
    currentLevel = LevelLoader::loadLevelFromPath(LevelLoader::getCurrentLevelPath());
    currentLevel->update(editorMode);
  }

  

  


}

/**
 * @brief get function that returns the screen width
 *
 * @return int screen width
 */
int SDLGraphicsProgram::GetScreenWidth()
{
  return this->screenWidth;
}

/**
 * @brief get function that returns the screen height
 *
 * @return int screen height
 */
int SDLGraphicsProgram::GetScreenHeight()
{
  return this->screenHeight;
}

// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram()
{

  ResourceManager::getInstance().shutDown();
  // Destroy Renderer
  SDL_DestroyRenderer(gRenderer);
  // Destroy window
  SDL_DestroyWindow(gWindow);
  // Point gWindow to NULL to ensure it points to nothing.
  gRenderer = NULL;
  gWindow = NULL;
  // Quit SDL subsystems
  SDL_Quit();
}

/**
 * @brief updates OpenGL
 *
 * @param moveLeft, type bool
 * @param moveRight, type bool
 * @param reset, type bool
 */
void SDLGraphicsProgram::update(bool moveLeft, bool moveRight, bool moveJump, bool reset)
{
  currentLevel->update(editorMode);

}

/**
 * @brief Render function for our main game
 *
 */
void SDLGraphicsProgram::render()
{
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);

  currentLevel->render(gRenderer);

  SDL_Texture *scoreText = GameStateManager::getInstance().renderScore(gRenderer, false);
  SDL_Rect scorePos;
  SDL_QueryTexture(scoreText, NULL, NULL, &scorePos.w, &scorePos.h);
  scorePos.x = GetScreenWidth() / 18;
  scorePos.y = (GetScreenHeight() / 18);
  SDL_RenderCopy(gRenderer, scoreText, NULL, &scorePos);

  if (GameStateManager::getInstance().gameIsOver)
  {
    SDL_Texture *gameText = GameStateManager::getInstance().renderMessage(gRenderer, false);
    SDL_Rect gamePos;
    SDL_QueryTexture(gameText, NULL, NULL, &gamePos.w, &gamePos.h);
    gamePos.x = GetScreenWidth() / 18;
    gamePos.y = GetScreenHeight() / 9;
    SDL_RenderCopy(gRenderer, gameText, NULL, &gamePos);
  }

  // LevelLoader::render(gRenderer);
  // player->render(gRenderer);
  // LevelLoader::render(gRenderer);
  // player->render(gRenderer);
  SDL_RenderPresent(gRenderer);
}

/**
 * @brief Main game loop that goes forever
 *
 */
void SDLGraphicsProgram::loop()
{
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Enable text input
  SDL_StartTextInput();
  bool isGameOver = false;
  bool moveLeft = false;
  bool moveRight = false;
  bool moveJump = false;
  this->reset = false;
  // variables to make frame rate 60FPD
  deque<Uint32> frameTimes;
  const size_t FRAME_COUNT = 60;
  Uint32 startTicks = SDL_GetTicks();
  const size_t DESIRED_FPS = 60;
  const size_t DESIRED_TICKS_PER_FRAME = 1000 / DESIRED_FPS;
  bool delete_object = false;

  // While application is running
  while (!quit)
  {
    InputManager::getInstance().resetForFrame();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
      InputManager::getInstance().handleEvent(e);
      if (InputManager::getInstance().isKeyPressed(SDLK_q))
      {
        quit = true;
      }
      if (InputManager::getInstance().isKeyPressed(SDLK_r))
      {
        currentLevel->removeAllObjects();
        currentLevel = LevelLoader::loadLevelFromPath(LevelLoader::getCurrentLevelPath());
        SoundManager::getInstance().reset();
        GameStateManager::getInstance().startUp();
      }
      int num_pressed = -1;
      if(InputManager::getInstance().isKeyDown(SDLK_0)){

        num_pressed = 0;
      }
      if(InputManager::getInstance().isKeyDown(SDLK_1)){

        num_pressed = 1;
      }
      if(InputManager::getInstance().isKeyDown(SDLK_2)){

        num_pressed = 2;
      }
      if(InputManager::getInstance().isKeyDown(SDLK_3)){

        num_pressed = 3;
      }
      if(InputManager::getInstance().isKeyDown(SDLK_4)){

        num_pressed = 4;
      }
      if(InputManager::getInstance().isKeyPressed(SDLK_d) && editorMode){

        delete_object = true;
        std::cout << "Deletion/Creation Mode is On " << std::endl;
      }
      if(InputManager::getInstance().isKeyPressed(SDLK_c)){

        delete_object = false;
        std::cout << "Deletion/Creation Mode is Off " << std::endl;
      }
      if(InputManager::getInstance().isKeyPressed(SDLK_s) && editorMode)
      {
        LevelLoader::writeToNewFile(currentLevel);
        quit = true;
        break;
      }
      if (InputManager::getInstance().isMousePressed(SDL_BUTTON_LEFT) && editorMode && delete_object)
      {
        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);
        std::shared_ptr<GameObject> curr = currentLevel->checkCoords(xMouse, yMouse);
        std::cout<< "mouse coords are x y: " << xMouse << " " << yMouse << std::endl;
        std::cout<< "num pressed is: " << num_pressed << std::endl;
        
        xMouse = round(xMouse / LevelLoader::textureWidth);
        xMouse *= LevelLoader::textureWidth;
        yMouse = round(yMouse / LevelLoader::textureHeight);
        yMouse *= LevelLoader::textureHeight;
      
        if (curr != 0) {
          currentLevel->removeObject(curr);
        }

        switch(num_pressed) {
          case 0:
            currentLevel->addObject(std::make_shared<Player>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight));
            break;
          case 1:
            currentLevel->addObject(std::make_shared<Block>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight));
            break;
          case 2:
            currentLevel->addObject(std::make_shared<Goal>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight));
            break;
          case 3:
            currentLevel->addObject(std::make_shared<Collectable>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight));
            break;
          case 4:
            currentLevel->addObject(std::make_shared<Enemy>(xMouse, yMouse,xMouse, yMouse - (1.5 * 40), LevelLoader::textureWidth, LevelLoader::textureHeight));
            break;
          
        }    
      }
    }



    isGameOver = GameStateManager::getInstance().levelIsOver;
    if (isGameOver) {
      currentLevel = LevelLoader::loadLevelFromPath(LevelLoader::getCurrentLevelPath());
      GameStateManager::getInstance().startUp();
    }

    if (!isGameOver)
    {
      update(moveLeft, moveRight, moveJump, reset);
    }
    moveJump = false;
    

    // Render using OpenGL
    render();
    // Update screen of our specified window

    Uint32 currTicks = SDL_GetTicks();

    // Uint32 seconds = currTicks * animationRate / 1000;
    // sprite = seconds % animationLength;
    Uint32 elapsedTicks = currTicks - startTicks;

    if (elapsedTicks < DESIRED_TICKS_PER_FRAME)
    {
      SDL_Delay(DESIRED_TICKS_PER_FRAME - elapsedTicks);
      currTicks = SDL_GetTicks();
      elapsedTicks = currTicks - startTicks;
    }

    startTicks = currTicks;

    frameTimes.push_back(elapsedTicks);

    while (frameTimes.size() > FRAME_COUNT)
    {
      frameTimes.pop_front();
    }

    assert(frameTimes.size() >= 1);
    assert(frameTimes.size() <= FRAME_COUNT);

    float avgTicksPerFrame = accumulate(frameTimes.begin(), frameTimes.end(), 0.0f) / frameTimes.size();
    float avgFps = 1.0f / (avgTicksPerFrame / 1000.0f);

    stringstream sstr;
    sstr << fixed << setprecision(3) << "FPS: " << avgFps << " ";
    // cout << sstr.str() << endl;
  }

  // Disable text input
  SDL_StopTextInput();
}

/**
 * @brief get function for the SDL Window
 *
 * @return SDL_Window*
 */
SDL_Window *SDLGraphicsProgram::getSDLWindow()
{
  return gWindow;
}

/**
 * @brief get function for the SDL Renderer
 *
 * @return SDL_Renderer*
 */
SDL_Renderer *SDLGraphicsProgram::getSDLRenderer()
{
  return gRenderer;
}
