#include "HealthComponent.hpp"


HealthComponent::HealthComponent(GameObject & gameObject, int health):
GenericComponent(gameObject) 
{
  mMaxHealth = health;
  mCurrentHealth = mMaxHealth;
}

void
HealthComponent::update(Level & level)
{

  if (!healthbarMade)
  {
    healthbarObject = make_shared<PiedHealthbar>(50, 8, &getGameObject(), *this);
    level.addObject(healthbarObject);
    healthbarMade = true;
  }

    GameObject & go = getGameObject();
    if(go.hit && mCurrentHealth > 0)
    {
      takeDamage(10);
      if(mCurrentHealth < 0){
        mCurrentHealth = 0;
      }
      go.hit = false;
    }

    if(mCurrentHealth == 0){
      go.isDead = true;
    }

    
    healthbarObject->update(level);
}

void
HealthComponent::takeDamage(int damage)
{
  if (mCurrentHealth - damage > mMaxHealth)
  {
    return;
  }
  mCurrentHealth -= damage;
}