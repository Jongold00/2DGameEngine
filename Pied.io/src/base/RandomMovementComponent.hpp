#ifndef RANDOM_MOVEMENT_COMPONENT
#define RANDOM_MOVEMENT_COMPONENT

#include "base/GenericComponent.hpp"

//! \brief A component that causes its game object to patrol back and forth.
class RandomMovementComponent: public GenericComponent {
public:

  RandomMovementComponent(GameObject & gameObject, float speed, float radius);
  
  virtual void update(Level & level);


private:

  void SetNewLocation();


  float mRadius;
  float mSpeed;

  float mStartX;
  float mStartY;

  float mLastX;
  float mLastY;

  float mToX;
  float mToY;
  int mCurrentStep;
  int mSteps = 0;

  
};

#endif