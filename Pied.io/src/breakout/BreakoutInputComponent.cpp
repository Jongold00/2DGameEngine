#ifndef BREAKOUT_INPUT_COMPONENT
#define BREAKOUT_INPUT_COMPONENT


#include <base/Component.hpp>
#include <base/GameObject.hpp>
#include <base/InputManager.hpp>
#include "Ball.hpp"
#include "base/Level.hpp"


class BreakoutInputComponent: public GenericComponent {
public:

  BreakoutInputComponent(GameObject & gameObject, float speed):
    GenericComponent(gameObject),
    mSpeed(speed)
  {
  }
  
  virtual void update(Level & level) override
  {
    bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    bool r_key = InputManager::getInstance().isKeyPressed(SDLK_r);
    bool l_key = InputManager::getInstance().isKeyPressed(SDLK_l);

    GameObject & gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

    if(!BreakoutGameStateManager::getInstance().isGameOver){
    if(r_key && level.respawn_possible){
      level.respawn_possible = false;
      level.addObject(std::make_shared<Ball>(level.w() / 2, level.h() / 2));
    }
    }

    if(l_key){

      BreakoutGameStateManager::getInstance().lang = !BreakoutGameStateManager::getInstance().lang;
      //apparently this is called 6 times if you press the l key once..
      std::cout<<"lang changed"<<std::endl;
      l_key = false;

    }
    
    if (left && !right) {
      pc->setVx(-mSpeed);
    } else if (!left && right) {
      pc->setVx(mSpeed);
    } else {
      pc->setVx(0.0f);
    }

    if (!level.objectOfTagExists(BreakoutBlock::BLOCK_TAG)) {
      BreakoutGameStateManager::getInstance().levelComplete();
    }
  }

private:

  float mSpeed;

};

#endif