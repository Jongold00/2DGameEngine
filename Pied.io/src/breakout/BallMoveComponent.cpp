#ifndef BALL_MOVE_COMPONENT
#define BALL_MOVE_COMPONENT


#include <base/Component.hpp>
#include <base/GameObject.hpp>
#include <base/Level.hpp>


class BallMoveComponent: public GenericComponent {
public:

  BallMoveComponent(GameObject & gameObject, float speed):
    GenericComponent(gameObject),
    mSpeed(speed)
  {
  }
  
  virtual void update(Level & level) override
  {

    GameObject & gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
    
    // Initial speed
    if (pc->vx() == 0) {
      pc->setVx(mSpeed);
    }
    if (pc->vy() == 0) {
      pc->setVy(mSpeed);
    }

    if (gameObject.y() > level.h()) {
      gameObject.isDead = true;
    }
    

    
  }

  void collision(Level & level, std::shared_ptr<GameObject> obj) override
  {
    int collider = obj->tag();
    switch (collider){
      case 0:
        // Ball collides with the Paddle
        getGameObject().physicsComponent()->setVy(-getGameObject().physicsComponent()->vy());
        break;
      case 10:
        // Ball collides with Right or Left Edge
        getGameObject().physicsComponent()->setVx(-getGameObject().physicsComponent()->vx());
        break;
      case 11:
        getGameObject().physicsComponent()->setVy(-getGameObject().physicsComponent()->vy());
        break;
      case 2:
        // Ball collides with a Block
        getGameObject().physicsComponent()->setVy(-getGameObject().physicsComponent()->vy());
        break;
      default:
        break;
    }
  }

private:

  float mSpeed;

};

#endif


		