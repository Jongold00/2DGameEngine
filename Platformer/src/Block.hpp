#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "LevelLoader.hpp"
#include "Hitbox.hpp"
#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include <SDL.h>
/**
 * @file block.hpp
 * @brief Header for block class
 */

/**
 * @brief Block class with position, and texture
 * @class: Block
 *
 * private members:
 * int x and y for position, texture variable,
 * SDL_Rects to generate the blocks
 *
 * public:
 * Constructor empty: default
 * Constructor params with position x and y
 *
 */
class Block : public GameObject
{
private:
    int x;
    int y;
    SDL_Texture *texture;

    SDL_Rect Dest;


public:
    Block();
    //~Block();

    Block(int x, int y, int w, int h);

    // returns whether a ball hit a box or not
};

#endif