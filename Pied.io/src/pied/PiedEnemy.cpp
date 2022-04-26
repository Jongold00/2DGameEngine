#include "PiedEnemy.hpp"
#include "base/SoundManager.hpp"

/**
 * @brief Construct a new Enemy:: Enemy object
 *
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
PiedEnemy::PiedEnemy(int x, int y, int w, int h, std::weak_ptr<GameObject> which) : GameObject(x, y, w, h, ENEMY_TAG)
{

  SDL_Rect Src;
  Src.x = 0;
  Src.y = 0;
  Src.w = 202;
  Src.h = 217;

  SDL_Texture *tex = ResourceManager::getInstance().getTexture("pied/enemy.png");



  ignores.push_back(1);
  ignores.push_back(2);
  ignores.push_back(3);
  ignores.push_back(4);

  setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));
  setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));
  lastFrameTime = SDL_GetTicks();
  addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 1));
  std::shared_ptr<StateComponent::State> patrolState = std::make_shared<PatrolState>(1.0f, x, y, x, y - 50 * 4.0f);
  chaseState = std::make_shared<ChaseState>(1.0f, which);
  std::shared_ptr<StateComponent::State> returnState = std::make_shared<MoveState>(1.0f, x, y);
  sc = std::make_shared<StateComponent>(*this);
  sc->setStartState(patrolState);
  sc->addTransition(patrolState, chaseState, std::make_shared<ObjectProximityTransition>(which, 50 * 5.0f));
  sc->addTransition(returnState, chaseState, std::make_shared<ObjectProximityTransition>(which, 50 * 3.0f));
  sc->addTransition(chaseState, returnState, std::make_shared<TimedTransition>(60));
  sc->addTransition(returnState, patrolState, std::make_shared<PointProximityTransition>(x, y, 50 / 4.0f));
  addGenericCompenent(sc);
}

void PiedEnemy::update(Level &level)
{
  float angleToPlayer = 0;

  currentFireCD -= SDL_GetTicks() - lastFrameTime;
  lastFrameTime = SDL_GetTicks();


  if (!healthMade)
  {
    addGenericCompenent(std::make_shared<HealthComponent>(*this, 40));
    healthMade = true;
  }

  for (auto genericComponent : genericComponents())
  {
    genericComponent->update(level);
  }

  for (auto go : level.getObjects())
  {
    if (go->tag() == PiedPlayer::PIED_PLAYER_TAG)
    {
      angleToPlayer = GetAngleToPlayer(go);
    }
  }

  if (sc->mCurrentState == chaseState)
  {
    HandleFiring(level, angleToPlayer);
  }
}

/**
 * @brief removes collectable from level
 *
 * @param level: type Level&
 * @param obj: type GameObject
 */
void PiedEnemy::death(Level &level, std::shared_ptr<GameObject> obj)
{
  hit = true;
  SoundManager::getInstance().playSoundEffect(1);
  PiedGameStateManager::getInstance().updateScore(5);
  level.removeObject(obj);
  // level.removeObject(obj);
}

float PiedEnemy::GetAngleToPlayer(std::shared_ptr<GameObject> go)
{
  int xPlayer, yPlayer;
  xPlayer = go->x();
  yPlayer = go->y();

  Vector2D enemyVec = Vector2D(this->x(), this->y());
  Vector2D playerVec = Vector2D(xPlayer, yPlayer);

  float radiansToDegrees = 180.0f / 3.14f;

  float theta = (float)atan2((double)(playerVec.y - enemyVec.y), (double)(playerVec.x - enemyVec.x));
  theta *= radiansToDegrees;

  return theta;
}

void PiedEnemy::HandleFiring(Level &level, float angle)
{
  if (currentFireCD <= 0)
  {
    float instX = this->x() + this->w() / 2;
    float instY = this->y() + this->h() / 2;
    float xOffset = ((this->w() / 2) + 10 * 1.3f) * cos(angle * (3.14f / 180.0f));
    float yOffset = ((this->h() / 2) + 10 * 1.3f) * sin(angle * (3.14f / 180.0f));
    level.addObject(make_shared<PiedBullet>((int)instX + xOffset, (int)instY + yOffset, 10, 10, angle, ignores));

    SoundManager::getInstance().playSoundEffect(0);

    currentFireCD = 2000;
  }
}