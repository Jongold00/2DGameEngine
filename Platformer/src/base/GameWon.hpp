#ifndef GAMEWON
#define GAMEWON


#include "base/GenericComponent.hpp"
#include "SDLGraphicsProgram.hpp"
#include <SDL.h>

//! \brief A component that implements the win condition (of a given tag) on collision.
class GameWon: public GenericComponent {
public:

  GameWon(GameObject & gameObject, int tag);
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:

  int mTag;
  
};

#endif