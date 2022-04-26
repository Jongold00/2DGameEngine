#include "base/RenderComponent.hpp"

RenderComponent::RenderComponent(GameObject & gameObject):
  Component(gameObject)
{
  flip = SDL_FLIP_NONE;
}


void RenderComponent::setAngle(float set) 
{
  mAngle = set;
}