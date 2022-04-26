#ifndef PIED_BOSS_HPP
#define PIED_BOSS_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "Health/PiedHealthbar.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/StateComponent.hpp"
#include "base/StatesandTransitions.hpp"
#include "PiedGameStateManager.hpp"
#include "base/RandomMovementComponent.hpp"
#include "PiedPlayer.hpp"



class HealthComponent;

/**
 * 
 * @brief 
 * 
 */
class PiedBoss: public GameObject
{
    private:

    vector<int> ignores;

    int bulletsFired = 0;
    float currentAngle = 0.0f;


    //float fireCD = 5.0f;
    float currentFireCD = 5.0f;

    float lastFrameTime;


    bool healthMade = false;

    void HandleFiring(Level & level);

    public:
    PiedBoss(int x, int y, int w, int h);
    ~PiedBoss() = default;

    static const int BOSS_TAG = 4;

     // removes collectable from a level
    void death(Level & level, std::shared_ptr<GameObject> obj) override;
    void update(Level & level) override;
};

#endif