#include "base/RemoveOnCollideComponent.hpp"

RemoveOnCollideComponent::RemoveOnCollideComponent(GameObject & gameObject, int tag):
  GenericComponent(gameObject),
  mTag(tag)
{

}

void
RemoveOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
  if (obj->tag() == mTag && !obj->isDead) {
    obj->isDead = true;
    obj->hit = true;
  }
}
