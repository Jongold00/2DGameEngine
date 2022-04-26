#ifndef PIED_PLAYER_INPUT
#define PIED_PLAYER_INPUT

#include "base/SDLGraphicsProgram.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/TinyMath.hpp"
#include <cmath>
#include "base/InputManager.hpp"
#include "PiedPlayer.hpp"
#include "PiedBullet.hpp"
#include "PiedEnemy.hpp"
#include "PiedCollectible.hpp"

class PiedPlayer;
class PiedExpTracker;

class PiedPlayerInputComponent: public GenericComponent {
public:

  PiedPlayerInputComponent(GameObject & gameObject, float speed, float screenW, float screenH, PiedPlayer & ps, shared_ptr<PiedExpTracker> exp);
  
  virtual void update(Level & level) override;

  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;


private:

    PiedPlayer & playerScript;

    shared_ptr<PiedExpTracker> expScript;

    Vector2D currentVelocity = Vector2D();

    float mSpeed = 0;

    float speedEpsilon = 0.0001;

    //int firingCD = 500; // in miliseconds
    vector<int> ignores;

    int currentFireCD = 0;

    int lastFrameTime = 0;

    int justTookDamage = 0;

    int healthRegenTimer = 0;


    float mScreenW;
    float mScreenH;

    float GetAngleToMouse(GameObject & go);


    void HandleFiring(Level & level, float angle);



};


#endif