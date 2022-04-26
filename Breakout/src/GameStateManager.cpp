
#include "GameStateManager.hpp"

using namespace std;

/**
 * @file GameStateManager.cpp
 * @brief Generates and moderates game state to determine if game has finished
 */

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
  this->lang = false;
  this->isGameOver = false;
}

/**
 * @brief initializes variables to base when game is shutDown
 *
 */
void GameStateManager::shutDown()
{
  if(this->lives == 0){
    this->endMessage = "You Lose!";
  }
  else{
    this->endMessage = "You Win!";
  }

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

int GameStateManager::getCurrentLevel()
{
  return currentLevel;
}


void GameStateManager::levelComplete()
{
  currentLevel++;
}
/**
 * @brief render function that displays the score using SDL Renderer
 *
 * @param gRenderer
 * @return SDL_Texture, the score to display
 */
SDL_Texture *GameStateManager::renderScore(SDL_Renderer *gRenderer)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Score: " + to_string(score), "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }

    //std::cout << "lang is" << lang << std::endl;
    return tex;

}

  SDL_Texture *GameStateManager::renderLives(SDL_Renderer *gRenderer)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Lives: " + to_string(lives), "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}

  SDL_Texture *GameStateManager::renderMessage(SDL_Renderer *gRenderer)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Texture *tex = ResourceManager::getInstance().renderText(endMessage, "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}



