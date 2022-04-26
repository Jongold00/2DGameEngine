// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "SDLGraphicsProgram.hpp"
#include <SDL.h>
// #include <SDL2_image/SDL_image.h>
#include "ResourceManager.hpp"
#include "BlockManager.hpp"
#include <Paddle.hpp>
#include "GameStateManager.hpp"
#include <Ball.hpp>
#include "TinyMath.hpp"
#include <deque>
#include <cassert>
#include <numeric>
#include <iomanip>

/**
 * @file SDLGraphicsProgram.cpp
 * @brief Window generation for game to be displayed
 */

/**
 * @brief Loads in textures from file onto renderer
 * 
 * @param file, type const string& 
 * @param ren, type SDL_Renderer*
 * @return SDL_Texture* 
 */
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);

// VARIABLES
static const int ROWS = 3;
static const int COLS = 8;
// Ball and Paddle object instances
Ball bvar;
Paddle pad;


/**
 * @brief Construct a new SDLGraphicsProgram::SDLGraphicsProgram object
 * Returns a true or false value based on successful completion of setup.
 * @param w, type int, width of the window
 * @param h, type int, height of window
 */
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) : screenHeight(h), screenWidth(w)
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
    gWindow = SDL_CreateWindow("Lab", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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

  GameStateManager::getInstance().startUp();
  // If initialization did not work, then print out a list of errors in the constructor.
  if (!success)
  {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  }
  else
  {
    std::cout << "No SDL errors Detected in during init of GameManager\n\n";
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

  BlockManager::getInstance().startUp(ROWS, COLS, w, h);

  if (!success)
  {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  }
  else
  {
    std::cout << "No SDL errors Detected in during init of BlockManager\n\n";
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

  // set the width and texture of paddle
  pad = Paddle("paddleRed.bmp", w / 15);
  pad.x = w / 2;
  // set the spawning position of a ball
  bvar = Ball(w / 10, (h / 10) * 9);
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
  BlockManager::getInstance().shutDown();
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
 * @param allDestroyed, type bool
 */
void SDLGraphicsProgram::update(bool moveLeft, bool moveRight, bool allDestroyed, bool langCheck)
{
  // checks if we have to destroy all blocks
  if (allDestroyed)
  {
    float score = BlockManager::getInstance().DestroyBlocks();
    GameStateManager::getInstance().updateScore(score);

  }

  if(BlockManager::getInstance().GetRemainingBlocks() == 0){
    GameStateManager::getInstance().levelComplete();
    if (GameStateManager::getInstance().currentLevel >= ResourceManager::getInstance().getNumLevels()) {
      GameStateManager::getInstance().isGameOver = true;
      GameStateManager::getInstance().shutDown();

    }
    else {
    BlockManager::getInstance().loadLevelFromPath(ResourceManager::getInstance().getCurrentLevel(), GetScreenWidth(), GetScreenHeight());

    }

  }

  GameStateManager::getInstance().lang = langCheck;
  //std::cout << "is the language hindi? " << GameStateManager::getInstance().lang << std::endl;



  // checks if ball hits the block or paddle
  bool blockHit = BlockManager::getInstance().CheckHitboxes(bvar.x + 11, bvar.y + 11);
  bool paddleHit = pad.CheckHitbox(bvar.x + 11, bvar.y + 11);

  if (blockHit) 
  {
    // handle collisions and stuff
    bvar.vel.y *= -1;
    //BlockManager::getInstance().blocks.erase(&blockHit);
    GameStateManager::getInstance().updateScore(1);
    SoundManager::getInstance().playSoundEffect(0);

  }


  // player lost condition
  if (bvar.y >= GetScreenHeight())
  {
    GameStateManager::getInstance().updateLives();
    // game over condition: lost all lives
    if (GameStateManager::getInstance().lives == 0)
    {
      GameStateManager::getInstance().isGameOver = true;
      GameStateManager::getInstance().shutDown();
      // stop the ball, maybe destroy it's constructor?
      bvar.vel.y = 0;
    }

    else
    {
      bvar = Ball(GetScreenWidth() / 10, (GetScreenHeight() / 10) * 9);
      GameStateManager::getInstance().score = 0;
    }
  }

  // ball hits screen ends
  if (bvar.x <= 0 || bvar.x >= GetScreenWidth())
  {
    SoundManager::getInstance().playSoundEffect(0);
    bvar.vel.x *= -1;
  }

    // collision that changes direction of ball
  if (bvar.y <= 0)
  {
    SoundManager::getInstance().playSoundEffect(0);
    bvar.vel.y *= -1;
  }

  // change direction of ball once it hits the paddle
  if (paddleHit)
  {
    SoundManager::getInstance().playSoundEffect(0);
    bvar.vel.y *= -1;
  }

  // move the paddle left
  if (moveLeft)
  {
    if (pad.x > 0)
    {
      pad.x -= pad.speed;
    }
  }
  // move the paddle right
  if (moveRight)
  {
    if (pad.x + pad.width < GetScreenWidth())
    {
      pad.x += pad.speed;
    }
  }

  // adds velocity to the ball
  bvar.y -= bvar.vel.y;
  bvar.x -= bvar.vel.x;
}

/**
 * @brief Render function for our main game
 *
 */
void SDLGraphicsProgram::render()
{


  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);

  

  if(GameStateManager::getInstance().isGameOver){
    //std::cout << "GAME OVER" << std::endl;

  SDL_Texture *messageText = GameStateManager::getInstance().renderMessage(gRenderer);
  SDL_Rect messagePos;
  SDL_QueryTexture(messageText, NULL, NULL, &messagePos.w, &messagePos.h);
  messagePos.x = (GetScreenWidth() / 10) + 425;
  messagePos.y = (GetScreenHeight() / 10) * 6;
  SDL_RenderCopy(gRenderer, messageText, NULL, &messagePos);
  }

  // Display the score text on the bottom left of the screen
  BlockManager::getInstance().render(gRenderer);
  SDL_Texture *scoreText = GameStateManager::getInstance().renderScore(gRenderer);
  SDL_Rect scorePos;
  SDL_QueryTexture(scoreText, NULL, NULL, &scorePos.w, &scorePos.h);
  scorePos.x = GetScreenWidth() / 10;
  scorePos.y = (GetScreenHeight() / 10) * 9;

  // Display the lives text on the bottom right of the screen
  SDL_Texture *livesText = GameStateManager::getInstance().renderLives(gRenderer);
  SDL_Rect livesPos;
  SDL_QueryTexture(livesText, NULL, NULL, &livesPos.w, &livesPos.h);
  livesPos.x = (GetScreenWidth() / 10) + 200;
  livesPos.y = (GetScreenHeight() / 10) * 9;

  // Display the paddle on the screen
  SDL_Rect dst;
  SDL_QueryTexture(pad.tex, NULL, NULL, &dst.w, &dst.h);
  dst.x = pad.x;
  dst.y = pad.y;

  // Display the ball on the screen
  SDL_Rect dst_2;
  SDL_QueryTexture(bvar.tex, NULL, NULL, &dst_2.w, &dst_2.h);
  dst_2.x = bvar.x;
  dst_2.y = bvar.y;

  SDL_RenderCopy(gRenderer, pad.tex, NULL, &dst);
  SDL_RenderCopy(gRenderer, bvar.tex, NULL, &dst_2);
  SDL_RenderCopy(gRenderer, scoreText, NULL, &scorePos);
  SDL_RenderCopy(gRenderer, livesText, NULL, &livesPos);


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

  bool moveLeft = false;
  bool moveRight = false;
  bool allDestroyed = false;
  // variables to make frame rate 60FPD
  deque<Uint32> frameTimes;
  const size_t FRAME_COUNT = 60;
  Uint32 startTicks = SDL_GetTicks();
  const size_t DESIRED_FPS = 60;
  const size_t DESIRED_TICKS_PER_FRAME = 1000 / DESIRED_FPS;

  bool langCheck = false;

  // While application is running
  while (!quit)
  {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
      // controls what happens when holding a key
      if (e.type == SDL_KEYDOWN)
      {

        switch (e.key.keysym.sym)
        {
        // user press 'q'
        case SDLK_q:
          quit = true;
          break;
        // user press 'x'
        case SDLK_x:
          std::cout << "All blocks destroyed!" << std::endl;
          allDestroyed = true;
          break;
        // user press left arrow key
        case SDLK_LEFT:
          moveLeft = true;
          moveRight = false;
          break;
        // user press right arrow key
        case SDLK_RIGHT:
          moveLeft = false;
          moveRight = true;
          break;
        // user press 'l'
        case SDLK_l:
        langCheck = !langCheck;
        //render();
        std::cout << "language change requested" << std::endl;
        break;
        }
      }

      else if (e.type == SDL_KEYUP)
      {

        switch (e.key.keysym.sym)
        {

        case SDLK_LEFT:
          moveLeft = false;
          break;

        case SDLK_RIGHT:
          moveRight = false;
          break;
        }
      }
    }

    // If you have time, implement your frame capping code here
    // Otherwise, this is a cheap hack for this lab.
    // SDL_Delay(250);


    if(!GameStateManager::getInstance().isGameOver){
      update(moveLeft, moveRight, allDestroyed, langCheck);
      allDestroyed = false;
    }
    
    if(allDestroyed){
      allDestroyed = false;
    }

    // Render using OpenGL
    render();
    // Update screen of our specified window

    Uint32 currTicks = SDL_GetTicks();
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
