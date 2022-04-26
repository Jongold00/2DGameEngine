#include "PiedPlayer.hpp"
#include "PiedPlayerInput.hpp"


/**
 * @brief Construct a new Player:: Player object
 *
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
PiedPlayer::PiedPlayer(int x, int y, int w, int h) : GameObject(x, y, w, h, PIED_PLAYER_TAG)
{

  SDL_Rect Src;
  Src.x = 0;
  Src.y = 0;
  Src.w = 590;
  Src.h = 594;

  SDL_Texture * tex = ResourceManager::getInstance().getTexture("pied/pie.png");

  setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));
  setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));

  shared_ptr<PiedExpTracker> exp = std::make_shared<PiedExpTracker>(*this, *this);
  expScript = exp;

  addGenericCompenent(std::make_shared<PiedPlayerInputComponent>(*this, speed, 900, 600, *this, exp));
  addGenericCompenent(exp);

  addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, PiedCollectible::COLLECTABLE_TAG));

}

void
PiedPlayer::update(Level & level)
{

  if(!PiedGameStateManager::getInstance().isGameOver){

  if (!healthMade)
  {
    healthScript = std::make_shared<HealthComponent>(*this, 100);
    addGenericCompenent(healthScript);
    healthMade = true;
  }

  for (auto genericComponent: genericComponents()) {
    genericComponent->update(level);
  }
  }
}

int
PiedPlayer::getFiringCD()
{
  return firingCD;
}


float
PiedPlayer::getSpeed()
{
  return speed;
}

shared_ptr<PiedExpTracker>
PiedPlayer::getExpScript()
{
  return expScript;
}

shared_ptr<HealthComponent>
PiedPlayer::getHealthScript()
{
  return healthScript;
}

void
PiedPlayer::spendPointBulletSize()
{
  bulletSize += 5;
}

void
PiedPlayer::spendPointHealth()
{
  healthScript->mCurrentHealth += 20;
  healthScript->mMaxHealth += 15;
}

void
PiedPlayer::spendPointFireRate()
{
  firingCD /= 1.1f;
}

void
PiedPlayer::spendPointSpeed()
{
  speed *= 1.1f;
}

int
PiedPlayer::getBulletSize()
{
  return bulletSize;
}


/**
 * @brief removes collectable from level
 * 
 * @param level: type Level&
 * @param obj: type GameObject
 */
void PiedPlayer::death(Level & level, std::shared_ptr<GameObject> obj) 
{
  hit = true;
  
  //level.removeObject(obj);

  if (PiedGameStateManager::getInstance().lives <= 0) {
        PiedGameStateManager::getInstance().gameOver();
    }
    else{
      PiedGameStateManager::getInstance().updateLives();
    }

  
}


