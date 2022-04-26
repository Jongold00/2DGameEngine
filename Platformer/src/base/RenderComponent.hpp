#ifndef BASE_RENDER_COMPONENT
#define BASE_RENDER_COMPONENT

#include "base/Component.hpp"
#include <string>
#include <SDL.h>

//! \brief A component that handles rendering.
class RenderComponent: public Component {
public:
  
  RenderComponent(GameObject & gameObject);


  virtual void render(SDL_Renderer * renderer) = 0; //!< Do the render.

  virtual void step() = 0;

  virtual void setActiveAnim(std::string set) = 0;


  void flipRender(SDL_RendererFlip flipRender) 
  {
    flip = flipRender;
  }

  SDL_RendererFlip flip;


};

#endif
