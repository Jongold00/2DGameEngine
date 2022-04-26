#include "base/RandomMovementComponent.hpp"
#include "base/GameObject.hpp"

RandomMovementComponent::RandomMovementComponent(GameObject & gameObject, float speed, float radius):
  GenericComponent(gameObject),
  mRadius(radius),
  mSpeed(speed),
  mToX(gameObject.x()),
  mToY(gameObject.y())
{
  // 
  /**
 * @brief initialization for game patrol enemy . 
 * @class Patrol component class extended. 
 */
  mCurrentStep = 0;

  mStartX = gameObject.x();
  mStartY = gameObject.y();


}

void RandomMovementComponent::update(Level & level)
{
  // TODO: update position
  GameObject & go = getGameObject();
  


  if (mCurrentStep >= mSteps - 1) 
  {
    SetNewLocation();
  }
  else
  {
    ++mCurrentStep;

    float t = mCurrentStep / float(mSteps - 2);


    go.setX((1.0 - t) * mLastX + t * mToX);
    go.setY((1.0 - t) * mLastY + t * mToY);
  }
  
    

  
}

void
RandomMovementComponent::SetNewLocation()
{
  mLastX = getGameObject().x();
  mLastY = getGameObject().y();

  mToX = rand() % (int)mRadius + mStartX;
  mToY = rand() % (int)mRadius + mStartY;


  float dx = mToX - mLastX;
  float dy = mToY - mLastY;

  float length = sqrt(dx * dx + dy * dy);
  mSteps = length / mSpeed;
  mCurrentStep = 0;
}