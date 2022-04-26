#ifndef ENEMY
#define ENEMY

#include "base/ResourceManager.hpp"
#include "LevelLoader.hpp"
#include "base/SoundManager.hpp"
#include "base/GameObject.hpp"
#include "base/SpriteRenderComponent.hpp"
#include <algorithm>
#include "base/PatrolComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"


/**
 * 
 * @brief Enemy class
 * 
 */
class Enemy : public GameObject
{
private:


public:

    // current positions
    float x;
    float y;
    float pX;
    float pY;

    //point value
    float point_value;

    //texture of the enemy
    SDL_Texture *tex;

    // default constructor
    Enemy(int x, int y, int px, int py, int w, int h);

    // default deconstructor
    ~Enemy() = default;

    SDL_Rect Src;
    SDL_Rect Dst;


};

#endif