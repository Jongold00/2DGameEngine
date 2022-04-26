#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "BlockManager.hpp"

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
class Block
{
private:
    int x;
    int y;
    SDL_Texture *texture;

    SDL_Rect Src;
    SDL_Rect Dest;

public:
    Block();
    //~Block();

    Block(int x, int y);

    // renders the Block using SDL_Renderer
    void render(SDL_Renderer *ren);

    // initializes the values of a Block
    void init();

    // returns whether a ball hit a box or not
    bool CheckHitbox(int x, int y);
};

#endif