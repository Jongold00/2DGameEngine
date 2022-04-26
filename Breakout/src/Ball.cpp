#include <sstream>
#include "SDLGraphicsProgram.hpp"
#include "ResourceManager.hpp"
#include "Ball.hpp"
#include "TinyMath.hpp"

/**
 * @file ball.cpp
 * @brief Constructs ball object
 */

/**
 * @brief Constructor for new Ball:: Ball object
 * 
 * @param x: type int 
 * @param y: type int
 * set texture to the grey ball bmp 
 */
Ball::Ball(int x, int y){
    this->x = x;
    this->y = y;
    this->tex = ResourceManager::getInstance().getTexture("grey-ball.bmp");
}





