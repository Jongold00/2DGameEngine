#include "base/GameWon.hpp"
#include "base/Level.hpp"
#include "SoundManager.hpp"
#include "GameStateManager.hpp"
#include "LevelLoader.hpp"
#include "SDLGraphicsProgram.hpp"

GameWon::GameWon(GameObject &gameObject, int tag) : GenericComponent(gameObject),
                                                    mTag(tag)
{
}

void GameWon::collision(Level &level, std::shared_ptr<GameObject> obj)
{
  if (obj->tag() == mTag)
  {
    //SoundManager::getInstance().shutDown();
    //GameStateManager::getInstance().levelComplete();
  }
}