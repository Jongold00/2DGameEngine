#include "PiedGameStateManager.hpp"
#include "base/SoundManager.hpp"

using namespace std;

/**
 * @file PiedGameStateManager.cpp
 * @brief Generates and moderates game state to determine if game has finished
 */

/**
 * @brief get function that gives us the PiedGameStateManager
 *
 * @return PiedGameStateManager
 */
PiedGameStateManager &PiedGameStateManager::getInstance()
{
  static PiedGameStateManager *instance = new PiedGameStateManager();
  return *instance;
}

/**
 * @brief initializes variables to base level at the beginning of our game
 *
 */
void PiedGameStateManager::startUp()
{
  this->score = 0;
  this->lives = 1;
  this->endMessage = "";
  currentLevel = 0;
  this->lang = false;
  this->isGameOver = false;
  end_sfx = false;
  bossSpawned = false;
}

/**
 * @brief initializes variables to base when game is shutDown
 *
 */
void PiedGameStateManager::shutDown()
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
int PiedGameStateManager::updateScore(int delta)
{
  score += delta;
  return score;
}

/**
 * @brief reduces lives when player looses
 * 
 */
int PiedGameStateManager::updateLives(){
  lives = lives - 1;
  return lives;
}

int PiedGameStateManager::getCurrentLevel()
{
  return currentLevel;
}

void PiedGameStateManager::gameOver()
{
  isGameOver = true;
  if(lives <= 0 && !end_sfx){
    SoundManager::getInstance().playSoundEffect(3);
    end_sfx = true;
    endMessage = "You Lose!";

  }
  else if (!end_sfx){
    SoundManager::getInstance().playSoundEffect(2);
    end_sfx = true;
    endMessage = "You Won!";
  }
}


void PiedGameStateManager::levelComplete()
{
 
}

/**
 * @brief render function that displays the score using SDL Renderer
 *
 * @param gRenderer
 * @return SDL_Texture, the score to display
 */
SDL_Texture *PiedGameStateManager::renderScore(SDL_Renderer *gRenderer)
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

  SDL_Texture *PiedGameStateManager::renderLives(SDL_Renderer *gRenderer)
{
  SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *tex = ResourceManager::getInstance().renderText("Lives: " + to_string(lives), "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}

  SDL_Texture *PiedGameStateManager::renderMessage(SDL_Renderer *gRenderer)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Texture *tex = ResourceManager::getInstance().renderText(endMessage, "sample.ttf", color, 50, lang, gRenderer);
    if (tex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    return tex;
}



