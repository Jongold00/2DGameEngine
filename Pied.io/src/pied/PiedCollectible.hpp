#ifndef PIED_COLLECTIBLE_HPP
#define PIED_COLLECTIBLE_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "Health/PiedHealthbar.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "PiedPlayer.hpp"
#include "PiedGameStateManager.hpp"


class HealthComponent;

/**
 * @brief 
 * 
 */
class PiedCollectible: public GameObject
{
    private:
    
        shared_ptr<HealthComponent> healthScript = nullptr;

    public:
    PiedCollectible(int x, int y, int w, int h);
    ~PiedCollectible() = default;

    static const int COLLECTABLE_TAG = 2;

    // removes collectable from a level
    void death(Level & level, std::shared_ptr<GameObject> obj) override;
    void update(Level & level) override;


    int health;
   
};

#endif