#include "PiedBullet.hpp"


/**
 * @brief Construct a new Player:: Player object
 *
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
PiedBullet::PiedBullet(int x, int y, int w, int h, float angle, vector<int> ignores) : GameObject(x, y, w, h, BULLET_TAG)
{

  SDL_Rect Src;

  Src.x = 0;
  Src.y = 0;
  Src.w = 3584;
  Src.h = 3518;

  SDL_Texture * tex = ResourceManager::getInstance().getTexture("pied/bullet.png");

  speed = 2.5f;
  damage = 1.0f;

  setRenderCompenent(std::make_shared<TextureRenderComponent>(*this, tex, Src));
  hit = false;
  shared_ptr<PhysicsComponent> pc = std::make_shared<PhysicsComponent>(*this, true);

  setPhysicsCompenent(pc);

  pc->setVx(speed * cos(angle * (3.14f / 180.0f)));
  pc->setVy(speed * sin(angle * (3.14f / 180.0f)));

  addGenericCompenent(make_shared<RemoveSelfOnCollideComponent>(*this, ignores));


 
}

 void PiedBullet::update(Level & level){

 }

/**
 * @brief removes collectable from level
 * 
 * @param level: type Level&
 * @param obj: type GameObject
 */
void PiedBullet::death(Level & level, std::shared_ptr<GameObject> obj) 
{
  level.removeObject(obj);

}