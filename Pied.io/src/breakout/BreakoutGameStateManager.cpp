
#include "BreakoutGameStateManager.hpp"

using namespace std;

/**
 * @file BreakoutGameStateManager.cpp
 * @brief Generates and moderates game state to determine if game has finished
 */

/**
 * @brief get function that gives us the BreakoutGameStateManager
 *
 * @return BreakoutGameStateManager
 */
BreakoutGameStateManager &BreakoutGameStateManager::getInstance()
{
  static BreakoutGameStateManager *instance = new BreakoutGameStateManager();
  return *instance;
}

/**
 * @brief initializes variables to base level at the beginning of our game
 *
 */
void BreakoutGameStateManager::startUp()
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
void BreakoutGameStateManager::shutDown()
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
int BreakoutGameStateManager::updateScore(int delta)
{
  score += delta;
  return score;
}

/**
 * @brief reduces lives when player looses
 * 
 */
int BreakoutGameStateManager::updateLives(){
  lives = lives - 1;
  return lives;
}

int BreakoutGameStateManager::getCurrentLevel()
{
  return currentLevel;
}

void BreakoutGameStateManager::gameOver()
{
  isGameOver = true;
}


void BreakoutGameStateManager::levelComplete()
{
  BlockManager::getInstance().loadNextLevel();
}

/**
 * @brief render function that displays the score using SDL Renderer
 *
 * @param gRenderer
 * @return SDL_Texture, the score to display
 */
SDL_Texture *BreakoutGameStateManager::renderScore(SDL_Renderer *gRenderer)
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

  SDL_Texture *BreakoutGameStateManager::renderLives(SDL_Renderer *gRenderer)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Lives: " + to_string(lives), "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}

  SDL_Texture *BreakoutGameStateManager::renderMessage(SDL_Renderer *gRenderer)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Texture *tex = ResourceManager::getInstance().renderText(endMessage, "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}



