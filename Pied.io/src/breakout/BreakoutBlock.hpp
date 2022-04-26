#ifndef BREAKOUT_BLOCK_HPP
#define BREAKOUT_BLOCK_HPP

#include "BlockManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/GameObject.hpp"
#include "BreakoutGameStateManager.hpp"

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
class BreakoutBlock : public GameObject
{
private:

    SDL_Texture* texture;

public:

    static const int BLOCK_TAG = 2;

    BreakoutBlock();
    //~Block();
    BreakoutBlock(int x, int y, int w, int h);

    void death(Level & level, std::shared_ptr<GameObject> obj);

};

#endif