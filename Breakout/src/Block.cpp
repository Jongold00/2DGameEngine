#include "Block.hpp"

/**
 * @file block.cpp
 * @brief Constructs block object and checks hitbox
 */

/**
 * @brief Constructor for new Block:: Block object
 *
 * @param x: type int
 * @param y: type int
 */
Block::Block(int x, int y)
{
    this->x = x;
    this->y = y;
}

/**
 * @brief Initializes values for new Block
 *
 */
void Block::init()
{
    this->texture = ResourceManager::getInstance().getTexture("element_blue_rectangle.bmp");

    Src.x = 0;
    Src.y = 0;
    Src.w = BlockManager::getInstance().textureWidth;
    Src.h = BlockManager::getInstance().textureHeight;

    Dest.x = x;
    Dest.y = y;
    Dest.w = BlockManager::getInstance().textureWidth;
    Dest.h = BlockManager::getInstance().textureHeight;
}

/**
 * @brief Renders a block based on Destination coordinates
 *
 * @param ren: SDL_Renderer
 *
 */
void Block::render(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren, texture, &Src, &Dest);
}

/**
 * @brief Checks if a ball hit a box
 *
 * @param x, int x coordinate of ball
 * @param y, int y coordinate of ball
 * @return true  if ball hit
 * @return false  if ball not hit
 */
bool Block::CheckHitbox(int x, int y)
{

    if (x < Dest.x + (Dest.w) && x > Dest.x)
    { // if the ball is between the x bounds
        if (y < Dest.y + (Dest.h) && y > Dest.y)
        { // if the ball is between the y bounds
            return true;
        }
    }
    return false;
}
