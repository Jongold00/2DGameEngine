#include "PiedCollectible.hpp"
#include "base/SoundManager.hpp"



/**
 * @brief Construct a new Collectible:: Collectible object
 *
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
PiedCollectible::PiedCollectible(int x, int y, int w, int h) : GameObject(x, y, w, h, COLLECTABLE_TAG)
{

  SDL_Rect Src;
  Src.x = 0;
  Src.y = 0;
  Src.w = 225;
  Src.h = 225;

  SDL_Texture * tex = ResourceManager::getInstance().getTexture("pied/collectible.png");

  setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));
  setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true)); 
  
  health = 20;
  hit = false;

  addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 1));

  
 
}

void
PiedCollectible::update(Level & level)
{
  
  if (healthScript == nullptr)
  {
    healthScript = make_shared<HealthComponent>(*this, health);
    addGenericCompenent(healthScript);
  }

  for (auto genericComponent: genericComponents()) {
    genericComponent->update(level);
  }


}

/**
 * @brief removes collectable from level
 * 
 * @param level: type Level&
 * @param obj: type GameObject
 */
void PiedCollectible::death(Level & level, std::shared_ptr<GameObject> obj) 
{
  PiedGameStateManager::getInstance().updateScore(1);
  SoundManager::getInstance().playSoundEffect(1);
  level.removeObject(obj);
  for (auto go : level.getObjects())
  {
    if (go->tag() == PiedPlayer::PIED_PLAYER_TAG) {
      shared_ptr<PiedPlayer> as_player = dynamic_pointer_cast<PiedPlayer>(go);
      as_player->getExpScript()->addExp(30);
    }
  }

}

