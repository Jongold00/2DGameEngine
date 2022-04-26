#include "Paddle.hpp"
// constructor that sets texture and width of paddle
Paddle::Paddle(int x, int y, int w, int h) : GameObject(x, y, w, h, PADDLE_TAG)
{

    SDL_Rect Src;


    Src.x = 0;
    Src.y = 0;
    Src.w = 104;
    Src.h = 24;

    tex = ResourceManager::getInstance().getTexture("breakout/paddleRed.png");
    setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true)); 
    addGenericCompenent(std::make_shared<BreakoutInputComponent>(*this, speed));


}