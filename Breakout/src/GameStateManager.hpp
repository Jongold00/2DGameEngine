#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <SDL.h>
#include "SDL_DEBUG.hpp"
#include <map>
#include <string>
#include "ResourceManager.hpp"
#include <vector>

using namespace std;

/**
 * @file GameStateManager.hpp
 * @brief Header for GameStateManager class
 */

/**
 * @brief GameStateManager that controls score and lives display
 * @class GameStateManager
 * private members:
 * Default constructors and deconstructors
 * copy and move constructors that should be avoided
 *
 * public members:
 * score variable and functions
 *
 */
class GameStateManager
{
private:
    GameStateManager() = default; // Private Singleton
    ~GameStateManager() = default;
    GameStateManager(GameStateManager const &) = delete; // Avoid copy constructor.
    void operator=(GameStateManager const &) = delete;   // Don't allow copy assignment.
    GameStateManager(GameStateManager &&) = delete;      // Avoid move constructor.
    void operator=(GameStateManager &&) = delete;        // Don't allow move assignment.
public:
    // get function for instance of Game State Manager
    static GameStateManager &getInstance();
    // variable to keep track of score in game
    int score;
    // variable that keeps track of lives in game
    int lives;
    // variable to keep track of current level
    int currentLevel;

    bool lang;

    bool isGameOver;

    string endMessage;

    // 'equivalent' to our constructor
    // do anything needed to initialize
    void startUp();

    // 'equivalent' to our destructor
    // make sure that any allocated resources are freed
    void shutDown();

    // function to update our score using input delta
    int updateScore(int delta);

    // function to reduce lives when player looses one
    int updateLives();

    //getter for the current level
    int getCurrentLevel();

    void levelComplete();

    // render function that uses SDL_Renderer
    SDL_Texture *renderScore(SDL_Renderer *gRenderer);
    
    // render function that uses SDL_Renderer
    SDL_Texture *renderLives(SDL_Renderer *gRenderer);

    //render function that uses SDL_Renderer
    SDL_Texture *renderMessage(SDL_Renderer *gRenderer);

  
};

#endif
