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

  SDL_RenderCopy(renderer, mTex, &mSrc, &Dest);
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
