#ifndef SPAWNING_COMPONENT
#define SPAWNING_COMPONENT

#include "base/GenericComponent.hpp"
#include "base/Level.hpp"
#include "pied/PiedCollectible.hpp"
#include "TinyMath.hpp"
#include <iostream>
#include <algorithm>


using namespace std;

//! \brief A component that handles rendering.
class SpawningComponent: public GenericComponent {
public:
  
  SpawningComponent(GameObject & gameObject, weak_ptr<GameObject> playerPtr);

  void update(Level & level) override;

private:
  
  weak_ptr<GameObject> mPlayerPtr;

  float mWidth;
  float mHeight;
  std::vector<Vector2D> coords;
  //Vector2D currCord;

  static const int maxCollectables = 36;
  static const int maxEnemies = 6;
};

class SpawningParent: public GameObject {
  public:

  SpawningParent(weak_ptr<GameObject> playerPtr);
};

#endif