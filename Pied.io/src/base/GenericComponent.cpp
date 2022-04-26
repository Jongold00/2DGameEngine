#include "base/GenericComponent.hpp"

GenericComponent::GenericComponent(GameObject & gameObject):
  Component(gameObject)
{
}

void
GenericComponent::update(Level & level)
{
}

void
GenericComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
}

void
GenericComponent::render(SDL_Renderer * renderer)
{
}

void
GenericComponent::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) 
{
}