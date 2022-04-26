#ifndef VERTICAL_EDGE_RECTANGLE_HPP
#define VERTICAL_EDGE_RECTANGLE_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TinyMath.hpp"
#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "BreakoutBlock.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/PhysicsComponent.hpp"



/**
 * @file verticaledgerectangle.hpp
 * @brief Header for the vertical edge rectangle class
 */

/**
 * @brief Vertical edge rectangle class with position and texture
 * @class: Vertical edge rectangle
 * public members: 
 * position variables x and y, Texture variable tex
 * Default constructor, constructor with position 
 * variables x and y, width w and height h as input
 */
class VerticalEdgeRectangle : public GameObject
{
private: 
    SDL_Texture * texture;

public:
    static const int VERTICALEDGERECTANGLE_TAG = 10;
    VerticalEdgeRectangle() = default;
    VerticalEdgeRectangle(int x, int y, int w, int h);
};

#endif


