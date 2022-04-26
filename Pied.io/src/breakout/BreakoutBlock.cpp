#include "BreakoutBlock.hpp"

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
BreakoutBlock::BreakoutBlock(int x, int y, int w, int h) : GameObject(x, y, w, h, BLOCK_TAG)
{

    SDL_Rect Src;

    Src.x = 0;
    Src.y = 0;
    Src.w = 64;
    Src.h = 32;

    texture = ResourceManager::getInstance().getTexture("breakout/element_blue_rectangle.png");
    setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, texture, Src));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));




}

void BreakoutBlock::death(Level & level, std::shared_ptr<GameObject> obj) 
{
  SoundManager::getInstance().playSoundEffect(0);
  BreakoutGameStateManager::getInstance().updateScore(1);
  level.removeObject(obj);

  
}