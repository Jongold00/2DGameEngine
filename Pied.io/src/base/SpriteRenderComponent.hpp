#ifndef BASE_SPRITE_RENDER_COMPONENT
#define BASE_SPRITE_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include <SDL.h>
#include <vector>
#include <map>
#include <string>

//! \brief Handles rendering a game object as a simple rectangle.
class SpriteRenderComponent: public RenderComponent {
public:

  SpriteRenderComponent(GameObject & gameObject, SDL_Rect src, std::map<std::string, std::pair<SDL_Texture*, int>>);


  virtual void setActiveAnim(std::string set) override;

  virtual void render(SDL_Renderer * renderer) override;
  virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override;

  virtual void step() override;


private:

  SDL_Rect mSrc;

  int currentFrame;
  std::pair<SDL_Texture*, int> currentAnim;
 
  // maps the name of the anim to a texture and how many frames are in that texture
  std::map<std::string, std::pair<SDL_Texture*, int>> mAnims;
  
  
};

#endif
