#include "Ball.hpp"

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
Ball::Ball(int x, int y) : GameObject(x, y, 20, 20, BALL_TAG) 
{
    SDL_Rect Src;
    Src.x = 0;
    Src.y = 0;
    Src.w = 22;
    Src.h = 22;


    texture = ResourceManager::getInstance().getTexture("breakout/grey-ball.png");
    setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, texture, Src));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, BreakoutBlock::BLOCK_TAG));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));
    addGenericCompenent(std::make_shared<BallMoveComponent>(*this, speed));



}
    
void
Ball::death(Level & level, std::shared_ptr<GameObject> obj)
{
    level.removeObject(obj);
    level.respawn_possible = true;
    if (BreakoutGameStateManager::getInstance().updateLives() <= 0) {
        BreakoutGameStateManager::getInstance().gameOver();
    }
}





