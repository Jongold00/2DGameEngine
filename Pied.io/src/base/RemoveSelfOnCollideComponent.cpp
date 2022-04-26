#include "base/RemoveSelfOnCollideComponent.hpp"

RemoveSelfOnCollideComponent::RemoveSelfOnCollideComponent(GameObject & gameObject, vector<int> ignoreTags):
  GenericComponent(gameObject),
  mIgnores(ignoreTags)
{

}

void
RemoveSelfOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
  for (int curr : mIgnores)
  {
    if (obj->tag() == curr)
    {
      return;
    }
  }    
  getGameObject().isDead = true;
  obj->hit = true;
}
