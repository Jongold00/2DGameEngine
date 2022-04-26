#ifndef PIED_HEALTHBAR_HPP
#define PIED_HEALTHBAR_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/RectRenderComponent.hpp"
#include "HealthComponent.hpp"


class HealthComponent;
class HealthbarComponent;
/**
 * @brief 
 * 
 */
class PiedHealthbar: public GameObject
{
    private:

        GameObject * mHostGO;
      
        //int fadeTime = 3000; // in miliseconds
        int currentFade = 0;
        int lastFrame = 0;

        shared_ptr<HealthbarComponent> sharedHealthbarComponent;

    public:
        PiedHealthbar(int w, int h, GameObject * hostGO, HealthComponent & health);
        ~PiedHealthbar() = default;

        void TookDamage();

        virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override;

        virtual void update(Level & level) override;


        static const int HEALTHBAR_TAG = 9999;
};

class HealthbarComponent : public GenericComponent
{
    public:

        HealthbarComponent(PiedHealthbar & gameObject, HealthComponent & health, GameObject * parent);
        
        virtual void update(Level & level) override;

        virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override;

        bool recalculate();

        PiedHealthbar & healthBar;
        HealthComponent & mHealth;
        GameObject * mParent;
        float health_pecentage = 1.0f;

    private:

       

        
    

};






#endif