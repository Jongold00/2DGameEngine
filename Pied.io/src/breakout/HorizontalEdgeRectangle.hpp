#ifndef HORIZONTAL_EDGE_RECTANGLE_HPP
#define HORIZONTAL_EDGE_RECTANGLE_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TinyMath.hpp"
#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "BreakoutBlock.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "Ball.hpp"



/**
 * @file horizontaledgerectangle.hpp
 * @brief Header for the horizontal edge rectangle class
 */

/**
 * @brief Horizontal edge rectangle class with position and texture
 * @class: Horizontal edge rectangle
 * public members: 
 * position variables x and y, Texture variable tex
 * Default constructor, constructor with position 
 * variables x and y, width w and height h as input
 */
class HorizontalEdgeRectangle : public GameObject
{
private: 
    SDL_Texture * texture;

public:
    static const int HORIZONTALEDGERECTANGLE_TAG = 11;
    HorizontalEdgeRectangle() = default;
    HorizontalEdgeRectangle(int x, int y, int w, int h);
};

#endif


