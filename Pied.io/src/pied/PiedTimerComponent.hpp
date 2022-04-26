#ifndef PIED_TIMER_COMPONENT_HPP
#define PIED_TIMER_COMPONENT_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include <cmath>


class PiedTimer: public GenericComponent {
public:

  PiedTimer(GameObject & gameObject, bool countUp);
  
  virtual void update(Level & level) override;
  virtual void render(SDL_Renderer * gRenderer, std::shared_ptr<GameObject> cam) override;
  

private:

    int minutes;
    int seconds;
    int milliseconds;
    bool goUp;

    void countUp();

    void countDown();



};


#endif