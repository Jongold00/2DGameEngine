#ifndef PIED_ENEMY_HPP
#define PIED_ENEMY_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "Health/PiedHealthbar.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/StateComponent.hpp"
#include "base/StatesandTransitions.hpp"
#include "PiedGameStateManager.hpp"



class HealthComponent;

/**
 * 
 * @brief 
 * 
 */
class PiedEnemy: public GameObject
{
    private:

    bool healthMade = false;

    public:
    PiedEnemy(int x, int y, int w, int h, std::weak_ptr<GameObject> which);
    ~PiedEnemy() = default;

    static const int ENEMY_TAG = 3;

     // removes collectable from a level
    void death(Level & level, std::shared_ptr<GameObject> obj) override;
    void update(Level & level) override;
    std::shared_ptr<StateComponent> sc;
    std::shared_ptr<StateComponent::State> chaseState;
    float GetAngleToPlayer(std::shared_ptr<GameObject> go);
    void HandleFiring(Level &level, float angle);

    vector<int> ignores;

    int currentFireCD = 0;

    int lastFrameTime = 0;

    float mScreenW;
    float mScreenH;
};

#endif