#ifndef BALL_HPP
#define BALL_HPP

#include "SDLGraphicsProgram.hpp"
#include "TinyMath.hpp"

/**
 * @file ball.hpp
 * @brief Header for ball class
 */

/**
 * @brief Ball class with position and texture
 * @class: Ball
 * public members: 
 * position variables x and y, Texture variable tex
 * Default constructor, constructor with position 
 * variables x and y as input
 */
class Ball
{
private:
public:
    int x;
    int y;
    Vector2D vel = Vector2D(3, 4);
    SDL_Texture *tex;
    Ball() = default;

    Ball(int x, int y);
};

#endif