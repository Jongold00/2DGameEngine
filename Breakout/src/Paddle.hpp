#ifndef PADDLE
#define PADDLE

#include "ResourceManager.hpp"
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
class Paddle
{
private:
public:
    float x;
    float y;
    SDL_Texture *tex;
    float speed = 10;
    int width;
    // default constructor
    Paddle() = default;
    // default deconstructor
    ~Paddle() = default;

    SDL_Rect Src;
    SDL_Rect Dst;

    // constructor that sets texture and width of paddle
    Paddle(const std::string file, int w)
    {
        x = 100;
        y = 575;
        tex = ResourceManager::getInstance().getTexture(file);
        SDL_QueryTexture(tex, NULL, NULL, &Dst.w, &Dst.h);
        width = Dst.w;

        Dst.x = x;
        Dst.y = y;
    }

    /**
     * @brief returns whether the ball hit the paddle or not
     *
     * @param x, type int
     * @param y, type int
     * @return true if ball hits paddle
     * @return false if ball doesnt hit paddle
     */
    bool CheckHitbox(int x, int y)
    {

        Dst.x = this->x;
        Dst.y = this->y;

        if (x < Dst.x + (Dst.w) && x > Dst.x)
        { // if the ball is between the x bounds
            if (y < Dst.y + (Dst.h) && y > Dst.y)
            { // if the ball is between the y bounds
                return true;
            }
        }

        return false;
    }
};

#endif
