#include "HorizontalEdgeRectangle.hpp"

/**
 * @file horizontaledgerectangle.cpp
 * @brief Constructs a horizontal edge rectangle object
 */

/**
 * @brief Constructor for new HorizontalEdgeRectangle:: HorizontalEdgeRectangle object
 * 
 * @param x: type int 
 * @param y: type int
 * @param w: type int
 * @param h: type int
 * set texture to nullptr
 */
HorizontalEdgeRectangle::HorizontalEdgeRectangle(int x, int y, int w, int h) : GameObject(x, y, w, h, HORIZONTALEDGERECTANGLE_TAG) 
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





