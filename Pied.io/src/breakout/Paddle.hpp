#ifndef PADDLE
#define PADDLE

#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "BreakoutInputComponent.cpp"
//#include "TinyMath.hpp"

/**
 * @file Paddle.hpp
 * @brief Header for Paddle class
 */

/**
 * @brief Paddle class that dictates position, speed, and texture
 * @class Paddle
 * public members:
 * float x and y for the position of the paddle
 * texture, speed, and width variables for paddle
 *
 */
class Paddle : public GameObject
{
private:
public:

    static const int PADDLE_TAG = 0;

    SDL_Texture *tex;
    float speed = 10;

    // default constructor
    Paddle() = default;

    // default deconstructor
    ~Paddle() = default;

    
    Paddle(int x, int y, int w, int h);
};

#endif
