#ifndef BASE_TEX_RENDER_COMPONENT
#define BASE_TEX_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include <SDL.h>

//! \brief Handles rendering a game object as a simple rectangle.
class TextureRenderComponent: public RenderComponent {
public:

  TextureRenderComponent(GameObject & gameObject, SDL_Texture * tex, SDL_Rect src);
  
  virtual void render(SDL_Renderer * renderer) override;
  virtual void render(SDL_Renderer * renderer, shared_ptr<GameObject> cam) override;

  virtual void setActiveAnim(std::string set) override;


  virtual void step() override;

private:

  SDL_Texture * mTex;
  SDL_Rect mSrc;
  
};

#endif