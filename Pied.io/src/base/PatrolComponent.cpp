#include "base/PatrolComponent.hpp"
#include "base/GameObject.hpp"

PatrolComponent::PatrolComponent(GameObject & gameObject, float toX, float toY, float speed):
  GenericComponent(gameObject)
{
  // 
  /**
 * @brief initialization for game patrol enemy . 
 * @class Patrol component class extended. 
 */
  mForward = true;
  mFromX = getGameObject().x();
  mFromY = getGameObject().y();
  mToX = toX;
  mToY = toY;
   
  const float dx = toX - mFromX;
  const float dy = toY - mFromY;
  float length = sqrt(dx * dx + dy * dy);
  mSteps = length / speed;
  mCurrentStep = 0;
}

void PatrolComponent::update(Level & level)
{
  // TODO: update position
  GameObject & go = getGameObject();
  
  if (mForward) 
  {
    ++mCurrentStep;
    if (mCurrentStep >= mSteps - 1) {
      mForward = false;
    }
  } 
  
  else {
    --mCurrentStep;
    if (mCurrentStep <= 0) {
      mForward = true;

    }
  }

  float t = mCurrentStep / float(mSteps - 2);
  go.setX((1.0 - t) * mFromX + t * mToX);
  go.setY((1.0 - t) * mFromY + t * mToY);

  
}