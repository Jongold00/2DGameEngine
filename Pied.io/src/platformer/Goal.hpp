#ifndef GOAL_HPP
#define GOAL_HPP

#include "LevelLoader.hpp"
#include "base/GameObject.hpp"
#include <SDL.h>
#include "base/SoundManager.hpp"
#include "GameStateManager.hpp"

/**
 * @file goal.hpp
 * @brief Header for goal class
 */

/**
 * @brief Goal class with position, and texture
 * @class: Goal
 *
 * private members:
 * int x and y for position, texture variable,
 * SDL_Rects to generate the goal
 *
 * public:
 * Constructor empty: default
 * Constructor params with position x and y
 *
 */
class Goal : public GameObject
{
private:
    int x;
    int y;
    SDL_Texture *texture;

    SDL_Rect Dest;

    void death(Level & level, std::shared_ptr<GameObject> obj) override;

public:
    Goal();
    static const int GOAL_TAG = 2;

    Goal(int x, int y, int w, int h);
};

#endif