#ifndef BASE_RENDER_COMPONENT
#define BASE_RENDER_COMPONENT

#include "base/Component.hpp"
#include <string>
#include <SDL.h>
#include <memory>


using namespace std;

//! \brief A component that handles rendering.
class RenderComponent: public Component {
public:
  
  RenderComponent(GameObject & gameObject);


  virtual void render(SDL_Renderer * renderer) = 0; //!< Do the render.
  virtual void render(SDL_Renderer * renderer, shared_ptr<GameObject> cam) = 0; //!< Do the render.


  virtual void step() = 0;

  virtual void setActiveAnim(std::string set) = 0;

  void setAngle(float set);

  void flipRender(SDL_RendererFlip flipRender) 
  {
    flip = flipRender;
  }

  SDL_RendererFlip flip;

  float mAngle = 0;


};

#endif
