#include "PiedHealthbar.hpp"

PiedHealthbar::PiedHealthbar(int w, int h, GameObject * hostGO, HealthComponent & health):
GameObject((int)hostGO->x(), (int)hostGO->y(), (int)w, (int)h, HEALTHBAR_TAG)
{
    mHostGO = hostGO;
    sharedHealthbarComponent = make_unique<HealthbarComponent>(*this, health, hostGO);
    addGenericCompenent(sharedHealthbarComponent);
    setRenderCompenent(make_shared<RectRenderComponent>(*this, 255, 255, 255));

}

void
PiedHealthbar::update(Level & level) 
{
   for (auto comp : genericComponents())
   {
       comp->update(level);
   }
}

void
PiedHealthbar::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) 
{
    currentFade -= SDL_GetTicks() - lastFrame;
    lastFrame = SDL_GetTicks();
    

    if (currentFade > 0 && !(mHostGO->isDead || mHostGO == nullptr))
    {
        if (renderComponent()) {
            renderComponent()->render(renderer, cam);
        }

        for (auto genericComponent: genericComponents()) {
            genericComponent->render(renderer, cam);
        }
    }
}

void
PiedHealthbar::TookDamage()
{
    currentFade = 3000;
}






HealthbarComponent::HealthbarComponent(PiedHealthbar & go, HealthComponent & health, GameObject * parent):
GenericComponent(go),
healthBar(go),
mHealth(health),
mParent(parent)
{

}

void
HealthbarComponent::update(Level & level) 
{ 
    GameObject & go = getGameObject();
    int yOffset = 30;
    go.setX(mParent->x());
    go.setY(mParent->y() - yOffset);
    if (mParent->isDead || mParent == nullptr)
    {
        go.isDead = true;
    }

    if (recalculate())
    {
        healthBar.TookDamage();
    }
}

void
HealthbarComponent::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) 
{
  GameObject & gameObject = getGameObject();
  SDL_Rect fillRect = { int(gameObject.x() - (cam->x() - (cam->w() / 2))), int(gameObject.y() - (cam->y() - (cam->h() / 2))), int(gameObject.w() * health_pecentage), int(gameObject.h()) };
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
}

bool
HealthbarComponent::recalculate()
{
    float new_percentage = (float)mHealth.mCurrentHealth  / (float)mHealth.mMaxHealth;
    bool changed = (abs(health_pecentage - new_percentage) > 0.001f);
    health_pecentage = new_percentage;
    return changed; // returns true if health changed

}

