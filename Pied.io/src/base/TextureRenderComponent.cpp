#include "base/TextureRenderComponent.hpp"
#include "base/GameObject.hpp"

TextureRenderComponent::TextureRenderComponent(GameObject & gameObject, SDL_Texture * tex, SDL_Rect src):
  RenderComponent(gameObject),
  mTex(tex),
  mSrc(src)
{
}

void
TextureRenderComponent::render(SDL_Renderer * renderer)
{
  const GameObject & gameObject = getGameObject();
  SDL_Rect Dest;
  Dest.x = gameObject.x();
  Dest.y = gameObject.y();
  Dest.w = gameObject.w();
  Dest.h = gameObject.h();


  SDL_Point * center = new SDL_Point();
  center->x = Dest.w / 2;
  center->y = Dest.h / 2;

  SDL_RenderCopyEx(renderer, mTex, &mSrc, &Dest, mAngle, center, SDL_FLIP_NONE);
}

void
TextureRenderComponent::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam)
{
  const GameObject & gameObject = getGameObject();
  SDL_Rect Dest;
  Dest.x = gameObject.x() - (cam->x() - (cam->w() / 2));
  Dest.y = gameObject.y() - (cam->y() - (cam->h() / 2));
  Dest.w = gameObject.w();
  Dest.h = gameObject.h();


  SDL_Point * center = new SDL_Point();
  center->x = Dest.w / 2;
  center->y = Dest.h / 2;

  
  SDL_RenderCopyEx(renderer, mTex, &mSrc, &Dest, mAngle, center, SDL_FLIP_NONE);
}

// don't implement
void
TextureRenderComponent::step()
{

}


// don't implement
void
TextureRenderComponent::setActiveAnim(std::string set)
{

}
