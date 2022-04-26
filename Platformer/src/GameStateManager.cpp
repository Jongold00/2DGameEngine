
#include "GameStateManager.hpp"

using namespace std;

/**
 * @brief get function that gives us the GameStateManager
 *
 * @return GameStateManager
 */
GameStateManager &GameStateManager::getInstance()
{
  static GameStateManager *instance = new GameStateManager();
  return *instance;
}

/**
 * @brief initializes variables to base level at the beginning of our game
 *
 */
void GameStateManager::startUp()
{
  this->score = 0;
  this->lives = 3;
  this->endMessage = "";
  currentLevel = 0;
  levelIsOver = false;
}

/**
 * @brief initializes variables to base when game is shutDown
 *
 */
void GameStateManager::shutDown(std::string message)
{
  this->endMessage = message;
  gameIsOver = true;
  SoundManager::getInstance().shutDown();
}

/**
 * @brief updates score using input delta
 *
 * @param delta, type int
 * @return int the current score
 */
int GameStateManager::updateScore(int delta)
{

  score += delta;
  return score;
}

/**
 * @brief reduces lives when player looses
 * 
 */
int GameStateManager::updateLives(){
  lives = lives - 1;
  return lives;
}

/**
 * @brief returns the current level
 * 
 * @return int 
 */
int GameStateManager::getCurrentLevel()
{
  return currentLevel;
}

/**
 * @brief changes the level upon completion
 * 
 */
void GameStateManager::levelComplete()
{
  if (LevelLoader::getNextLevelPath() != "") {
    levelIsOver = true;
  }
  else {
    std::cout << "shouldn't be here" << std::endl;
    shutDown("You Won!");
  }
}
/**
 * @brief render function that displays the score using SDL Renderer
 *
 * @param gRenderer
 * @return SDL_Texture, the score to display
 */
SDL_Texture *GameStateManager::renderScore(SDL_Renderer *gRenderer, bool lang)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Score: " + to_string(score), "sample.ttf", color, 20, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;

}

/**
 * @brief generates the lives as a text
 * 
 * @param gRenderer 
 * @param lang 
 * @return SDL_Texture* 
 */
SDL_Texture *GameStateManager::renderLives(SDL_Renderer *gRenderer, bool lang)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Lives: " + to_string(lives), "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}

/**
 * @brief generates a generic message
 * 
 * @param gRenderer 
 * @param lang 
 * @return SDL_Texture* 
 */
SDL_Texture *GameStateManager::renderMessage(SDL_Renderer *gRenderer, bool lang)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Texture *tex = ResourceManager::getInstance().renderText(endMessage, "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}


