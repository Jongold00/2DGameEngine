#ifndef BASE_RECT_RENDER_COMPONENT
#define BASE_RECT_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include <SDL.h>

//! \brief Handles rendering a game object as a simple rectangle.
class RectRenderComponent: public RenderComponent {
public:

  RectRenderComponent(GameObject & gameObject, Uint8 r, Uint8 g, Uint8 b);
  
  virtual void render(SDL_Renderer * renderer) override;
  virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override;
  virtual void step() override;
  virtual void setActiveAnim(std::string set) override;



private:

  Uint8 mR, mG, mB;
  
};

#endif
