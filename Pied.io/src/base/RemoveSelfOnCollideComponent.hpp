#ifndef REMOVE_SELF_ON_COLLIDE_COMPONENT
#define REMOVE_SELF_ON_COLLIDE_COMPONENT

#include "base/GenericComponent.hpp"

#include "base/Level.hpp"
#include "SoundManager.hpp"
#include "../pied/PiedPlayer.hpp"

//! \brief A component that removes a game object (of a given tag) on collision.
class RemoveSelfOnCollideComponent: public GenericComponent {
public:

  RemoveSelfOnCollideComponent(GameObject & gameObject, vector<int> ignoreTags);
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:
  vector<int> mIgnores;
};

#endif
