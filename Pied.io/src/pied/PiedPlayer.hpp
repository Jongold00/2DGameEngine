#ifndef PIED_PLAYER_HPP
#define PIED_PLAYER_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "PiedBullet.hpp"
#include "Health/HealthComponent.hpp"
#include "Health/PiedHealthbar.hpp"
#include "PiedExpTracker.hpp"

#include "base/RemoveOnCollideComponent.hpp"
#include "PiedGameStateManager.hpp"


class HealthComponent;



class PiedPlayer : public GameObject 
{
    private:
        float speed = 2;
        int firingCD = 500;
        int bulletSize = 10;

        shared_ptr<PiedExpTracker> expScript;
        shared_ptr<HealthComponent> healthScript;

        bool healthMade = false;
        
    public:



        PiedPlayer(int x, int y, int w, int h);
        ~PiedPlayer() = default;
        
         // removes collectable from a level
        void death(Level & level, std::shared_ptr<GameObject> obj) override;
        void update(Level & level) override;
        int getFiringCD();
        float getSpeed();

        shared_ptr<PiedExpTracker> getExpScript();
        shared_ptr<HealthComponent> getHealthScript();

        int getBulletSize();

        static const int PIED_PLAYER_TAG = 0;


        void spendPointHealth();
        void spendPointSpeed();
        void spendPointBulletSize();
        void spendPointFireRate();

};

#endif