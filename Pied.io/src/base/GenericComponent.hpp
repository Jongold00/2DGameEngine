#ifndef BASE_GENERIC_COMPONENT
#define BASE_GENERIC_COMPONENT

#include "base/Component.hpp"
#include <SDL.h>
#include <memory>

class Level;

//! \brief A generic component that can handle updating and collisions.
class GenericComponent: public Component {
public:
  
  GenericComponent(GameObject & gameObject);

  virtual void update(Level & level); //!< Update the object.
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj); //!< Handle a collision with the given object.
  virtual void render(SDL_Renderer * renderer);
  virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam); //!< Render the component on the camera's offset


};

#endif
