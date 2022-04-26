#include "base/SpriteRenderComponent.hpp"
#include "base/GameObject.hpp"

SpriteRenderComponent::SpriteRenderComponent(GameObject & gameObject, SDL_Rect src, std::map<std::string, std::pair<SDL_Texture*, int>> anims):
  RenderComponent(gameObject),
  mSrc(src),
  mAnims(anims)
{
  setActiveAnim("idle");
}



void
SpriteRenderComponent::setActiveAnim(std::string set)
{
  for (auto anim : mAnims) {
    if (set.compare(anim.first) == 0) 
    {
      currentAnim = anim.second;

      return;
    }
  }

  
  std::cout << "error: animation not found" << std::endl;
}

void
SpriteRenderComponent::step() 
{

  currentFrame = (currentFrame + 1) % currentAnim.second;
}


void
SpriteRenderComponent::render(SDL_Renderer * renderer)
{
  const GameObject & gameObject = getGameObject();

  SDL_Rect Src;
  Src.x = mSrc.w * currentFrame;
  Src.y = mSrc.y;
  Src.w = mSrc.w;
  Src.h = mSrc.h;


  SDL_Rect Dest;
  Dest.x = gameObject.x();
  Dest.y = gameObject.y();
  Dest.w = gameObject.w();
  Dest.h = gameObject.h();

  SDL_RendererFlip flipRender = flip;

  SDL_RenderCopyEx(renderer, currentAnim.first, &Src, &Dest, 0, NULL, flipRender);
}

void
SpriteRenderComponent::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam)
{
  const GameObject & gameObject = getGameObject();

  SDL_Rect Src;
  Src.x = mSrc.w * currentFrame;
  Src.y = mSrc.y;
  Src.w = mSrc.w;
  Src.h = mSrc.h;


  SDL_Rect Dest;
  Dest.x = gameObject.x() - (cam->x() - (cam->w() / 2));
  Dest.y = gameObject.y() - (cam->y() - (cam->h() / 2));
  Dest.w = gameObject.w();
  Dest.h = gameObject.h();

  SDL_RendererFlip flipRender = flip;

  SDL_RenderCopyEx(renderer, currentAnim.first, &Src, &Dest, 0, NULL, flipRender);
}
