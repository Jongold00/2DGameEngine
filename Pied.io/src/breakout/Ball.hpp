#ifndef BALL_HPP
#define BALL_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TinyMath.hpp"
#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "BreakoutBlock.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "BallMoveComponent.cpp"
#include "BreakoutGameStateManager.hpp"
#include "HorizontalEdgeRectangle.hpp"


/**
 * @file ball.hpp
 * @brief Header for ball class
 */

/**
 * @brief Ball class with position and texture
 * @class: Ball
 * public members: 
 * position variables x and y, Texture variable tex
 * Default constructor, constructor with position 
 * variables x and y as input
 */
class Ball : public GameObject
{
private: 
    SDL_Texture * texture;

public:
    static const int BALL_TAG = 1;
    float speed = 4;
    Ball() = default;
    Ball(int x, int y);
    void death(Level & level, std::shared_ptr<GameObject> obj);

};

#endif


