#ifndef HEALTH_HPP
#define HEALTH_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "PiedHealthbar.hpp"
#include <memory>
#include "../PiedPlayer.hpp"


class PiedHealthbar;



class HealthComponent : public GenericComponent
{
    public:

        HealthComponent(GameObject & gameObject, int health);
        
        void update(Level & level);

        void takeDamage(int damage);

        shared_ptr<PiedHealthbar> healthbarObject;

        int mCurrentHealth;
        int mMaxHealth;

        bool healthbarMade = false;

    private:

    

};

#endif