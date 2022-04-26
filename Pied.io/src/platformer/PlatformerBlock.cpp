#include "PlatformerBlock.hpp"

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
PlatformerBlock::PlatformerBlock(int x, int y, int w, int h) : GameObject(x, y, w, h, 1)
{
    SDL_Rect Src;
    Src.x = 0;
    Src.y = 0;
    Src.w = 48;
    Src.h = 48;
    this->texture = ResourceManager::getInstance().getTexture("platformer/row-1-column-1.png");
    setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, texture, Src));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));

}

