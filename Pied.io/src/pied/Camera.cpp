#include "Camera.hpp"



class CameraControlComponent : public GenericComponent 
{
  public:
    CameraControlComponent(GameObject & gameObject, shared_ptr<GameObject> player):
      GenericComponent(gameObject),
      mPlayer(player)
    {
    }
    
    virtual void update(Level & level) override
    {

      GameObject & go = getGameObject();
      go.setX(mPlayer->x());
      go.setY(mPlayer->y());
    }

  private:
    shared_ptr<GameObject> mPlayer;

    
};


Camera::Camera(int x, int y, int w, int h, shared_ptr<GameObject> player) : GameObject(x, y, w, h, CAMERA_TAG)
{
  addGenericCompenent(make_shared<CameraControlComponent>(*this, player));

}

