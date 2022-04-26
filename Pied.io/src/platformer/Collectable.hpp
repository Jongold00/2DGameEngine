#ifndef COLLECTABLE
#define COLLECTABLE

#include "base/ResourceManager.hpp"
#include "LevelLoader.hpp"
#include "base/SoundManager.hpp"
#include "base/GameObject.hpp"
#include "base/SpriteRenderComponent.hpp"
#include <algorithm>
#include "GameStateManager.hpp"


/**
 * 
 * @brief Collectable class
 * 
 */
class Collectable : public GameObject
{
private:


public:

    // current positions
    float x;
    float y;

    //point value
    float point_value;

    //texture of the collectable
    SDL_Texture *tex;

    // default constructor
    Collectable(int x, int y, int w, int h);
    // default deconstructor
    ~Collectable() = default;

    SDL_Rect Src;
    SDL_Rect Dst;

    static const int COLLECTABLE_TAG = 2;

    // removes collectable from a level
    void death(Level & level, std::shared_ptr<GameObject> obj) override;

};

#endif