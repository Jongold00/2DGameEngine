// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "SDLGraphicsProgram.hpp"


// TODO: Move this out from here!
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
/*
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);

// VARIABLES
static const int ROWS = 3;
static const int COLS = 8;
// Ball and Paddle object instances
Ball bvar;
Paddle pad;
*/

/**
 * @brief Construct a new SDLGraphicsProgram::SDLGraphicsProgram object
 * Returns a true or false value based on successful completion of setup.
 * @param level, type Level, level to be loaded
 */
SDLGraphicsProgram::SDLGraphicsProgram(std::shared_ptr<Level> level, bool editorMode):
  mLevel(level),
  mEditorMode(editorMode)
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
    gWindow = SDL_CreateWindow("Lab", 100, 100, mLevel->w(), mLevel->h(), SDL_WINDOW_SHOWN);
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

}

SDLGraphicsProgram::SDLGraphicsProgram(std::shared_ptr<Level> level, int w, int h):
  mLevel(level),
  mEditorMode(false)
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
    gWindow = SDL_CreateWindow("Lab", 100, 100, w, h, SDL_WINDOW_SHOWN);
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

}

/**
 * @brief get function that returns the screen width
 *
 * @return int screen width
 */
/*
int SDLGraphicsProgram::GetScreenWidth()
{
  return this->screenWidth;
}
*/
/**
 * @brief get function that returns the screen height
 *
 * @return int screen height
 */
/*
int SDLGraphicsProgram::GetScreenHeight()
{
  return this->screenHeight;
}
*/
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

// TODO: deleting booleans for input! We need to deal with them in ResourceManager::handleEvent!
/**
 * @brief updates OpenGL
 *
 * @param moveLeft, type bool
 * @param moveRight, type bool
 * @param allDestroyed, type bool
 * @param langCheck, type bool
 */
void SDLGraphicsProgram::update()
{
  mLevel->update(mEditorMode);
}

/**
 * @brief Render function for our main game
 *
 */
void SDLGraphicsProgram::render()
{
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);

  mLevel->render(gRenderer);

  SDL_RenderPresent(gRenderer);



  /* PLATFORMER CODE TO REIMPLEMENT

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



  */

  
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

  
  // variables to make frame rate 60 FPS

  deque<Uint32> frameTimes;
  const size_t FRAME_COUNT = 60;
  Uint32 startTicks = SDL_GetTicks();
  const size_t DESIRED_FPS = 60;
  const size_t DESIRED_TICKS_PER_FRAME = 1000 / DESIRED_FPS;



  // While application is running
  while (!quit)
  {
    InputManager::getInstance().resetForFrame();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.

      if (e.type == SDL_QUIT)
      {
        quit = true;
      }

      InputManager::getInstance().handleEvent(e);
    }

    // If you have time, implement your frame capping code here
    // Otherwise, this is a cheap hack for this lab.
    // SDL_Delay(250);

    // Render using OpenGL
    update();

    render();
    // Update screen of our specified window

    // FRAME CAP : START //
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
    // FRAME CAP : END //
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

void
SDLGraphicsProgram::loadNewLevel(shared_ptr<Level> set)
{
  mLevel = set;
}





/*

RANDOM PLATFORMER INPUT CODE

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





*/