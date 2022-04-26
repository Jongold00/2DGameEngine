#include "VerticalEdgeRectangle.hpp"

/**
 * @file verticaledgerectangle.cpp
 * @brief Constructs a vertical edge rectangle object
 */

/**
 * @brief Constructor for new VerticalEdgeRectangle:: VerticalEdgeRectangle object
 * 
 * @param x: type int 
 * @param y: type int
 * @param w: type int
 * @param h: type int
 * set texture to nullptr
 */
VerticalEdgeRectangle::VerticalEdgeRectangle(int x, int y, int w, int h) : GameObject(x, y, w, h, VERTICALEDGERECTANGLE_TAG) 
{
    SDL_Rect Src;
    Src.x = 0;
    Src.y = 0;
    Src.w = w;
    Src.h = h;


    texture = nullptr;
    setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, texture, Src));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));


}





