#include "PiedBoss.hpp"
#include "base/SoundManager.hpp"

/**
 * @brief Construct a new Enemy:: Enemy object
 *
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
PiedBoss::PiedBoss(int x, int y, int w, int h) : GameObject(x, y, w, h, BOSS_TAG)
{

  SDL_Rect Src;
  Src.x = 0;
  Src.y = 0;
  Src.w = 471;
  Src.h = 397;

  SDL_Texture *tex = ResourceManager::getInstance().getTexture("pied/boss.png");

  setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));
  setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));

  addGenericCompenent(std::make_shared<RandomMovementComponent>(*this, 1.f, 1000.f));

  ignores.push_back(1);
  ignores.push_back(2);
  ignores.push_back(3);
  ignores.push_back(4);

  
}

void PiedBoss::update(Level &level)
{

  if (!healthMade)
  {
    addGenericCompenent(std::make_shared<HealthComponent>(*this, 150));
    healthMade = true;
  }

  for (auto genericComponent : genericComponents())
  {
    genericComponent->update(level);
  }


  currentFireCD -= SDL_GetTicks() - lastFrameTime;

  lastFrameTime = SDL_GetTicks();

  if (currentFireCD <= 0) 
  {
    HandleFiring(level);
  }
}

/**
 * @brief removes collectable from level
 *
 * @param level: type Level&
 * @param obj: type GameObject
 */
void PiedBoss::death(Level &level, std::shared_ptr<GameObject> obj)
{
  hit = true;
  SoundManager::getInstance().playSoundEffect(1);
  PiedGameStateManager::getInstance().updateScore(9001);
  PiedGameStateManager::getInstance().gameOver();
  level.removeObject(obj);
}



void 
PiedBoss::HandleFiring(Level & level)
{


  float instX;
  float instY;

  float xOffset;
  float yOffset;


  if (bulletsFired < 72)
  {
    currentAngle += 10.0f;

    instX = x() + w() / 2;
    instY = y() + h() / 2;
    xOffset = ((w() / 2) + 50 * 1.3f) * cos(currentAngle * (3.14f / 180.0f));
    yOffset = ((h() / 2) + 50 * 1.3f) * sin(currentAngle * (3.14f / 180.0f));

    level.addObject(make_shared<PiedBullet>((int)instX + xOffset, (int)instY + yOffset, 15, 15, currentAngle, ignores));

    SoundManager::getInstance().playSoundEffect(0);
    currentFireCD = 50;
    bulletsFired++;

  }
  else
  {
    currentAngle = 0.f;
    bulletsFired = 0;
    currentFireCD = 10000;
  }
  






}