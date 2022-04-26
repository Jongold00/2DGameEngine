#include "PiedPlayerInput.hpp"
#include "base/SoundManager.hpp"


  PiedPlayerInputComponent::PiedPlayerInputComponent(GameObject & gameObject, float speed, float screenW, float screenH, PiedPlayer & ps, shared_ptr<PiedExpTracker> exp):
    GenericComponent(gameObject),
    playerScript(ps),
    expScript(exp),
    mSpeed(speed),
    mScreenW(screenW),
    mScreenH(screenH)
  {
    lastFrameTime = SDL_GetTicks();
    playerScript = ps;
    ignores.push_back(0);
  }

  void
  PiedPlayerInputComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
  {
      if (obj->tag() == PiedEnemy::ENEMY_TAG && justTookDamage <= 0)
      {
        if (getGameObject().hit) {
          std::cout << "i got hit" << std::endl;
        }
        justTookDamage = 100;
        shared_ptr<HealthComponent> dfkasnf = playerScript.getHealthScript();
        std::cout << "wtf is this " << dfkasnf << std::endl;
        dfkasnf->takeDamage(10);
      }

      if (obj->tag() == PiedCollectible::COLLECTABLE_TAG && justTookDamage <= 0)
      {
        justTookDamage = 250;
        playerScript.getHealthScript()->takeDamage(10);
      }
  }
  
  void PiedPlayerInputComponent::update(Level & level)
  {

    std::shared_ptr<RenderComponent> rc = getGameObject().renderComponent();

    float x = getGameObject().x();
    float y = getGameObject().y();




    float angleToMouse = GetAngleToMouse(getGameObject());
    mSpeed = playerScript.getSpeed();



    rc->setAngle(angleToMouse);


    bool up = InputManager::getInstance().isKeyDown(SDLK_w);
    bool down = InputManager::getInstance().isKeyDown(SDLK_s);
    bool left = InputManager::getInstance().isKeyDown(SDLK_a);
    bool right = InputManager::getInstance().isKeyDown(SDLK_d);

    bool firing = InputManager::getInstance().isMouseDown(SDL_BUTTON_LEFT);


    bool onePressed = InputManager::getInstance().isKeyPressed(SDLK_1);
    bool twoPressed = InputManager::getInstance().isKeyPressed(SDLK_2);
    bool threePressed = InputManager::getInstance().isKeyPressed(SDLK_3);
    bool fourPressed = InputManager::getInstance().isKeyPressed(SDLK_4);



    if (onePressed)
    {
        expScript->spendPointHealth();
        
    }

    if (twoPressed)
    {
        expScript->spendPointSpeed();
       
    }

    if (threePressed)
    {
        expScript->spendPointBulletSize();
       
    }

    if (fourPressed)
    {
        expScript->spendPointFireRate();
        
    }

    currentFireCD -= SDL_GetTicks() - lastFrameTime;

    justTookDamage -= SDL_GetTicks() - lastFrameTime;

    healthRegenTimer  -= SDL_GetTicks() - lastFrameTime;

    lastFrameTime = SDL_GetTicks();


    if (healthRegenTimer <= 0) 
    {
      playerScript.getHealthScript()->takeDamage(-1);
      healthRegenTimer = 2900;
    }

    if (firing)
    {
      HandleFiring(level, angleToMouse);
     
    }


    if (up) 
    {
      currentVelocity.y -= 0.0166f * mSpeed;
    }
    if (down) 
    {
      currentVelocity.y += 0.0166f * mSpeed;
    }

    if (!up && !down) 
    {
      currentVelocity.y /= 1.01;
      if (abs(currentVelocity.y) <= speedEpsilon)
      {
        currentVelocity.y = 0.0f;
      }
    }

    if (left) 
    {
      currentVelocity.x -= 0.0166f * mSpeed;
    }
    if (right) 
    {
      currentVelocity.x += 0.0166f * mSpeed;
    }

    if (!left && !right) 
    {
      currentVelocity.x /= 1.01;
      if (abs(currentVelocity.x) <= speedEpsilon)
      {
        currentVelocity.x = 0.0f;
      }
    }


    x += currentVelocity.x;
    y += currentVelocity.y;

    getGameObject().setX(x);
    getGameObject().setY(y);


  }

  float PiedPlayerInputComponent::GetAngleToMouse(GameObject & go)
  {
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    Vector2D middleVec = Vector2D(mScreenW / 2, mScreenH / 2);
    Vector2D mouseVec = Vector2D(xMouse, yMouse);


    float radiansToDegrees = 180.0f / 3.14f;

    float theta = (float)atan2((double)(mouseVec.y - middleVec.y), (double)(mouseVec.x - middleVec.x));
    theta *= radiansToDegrees;

    return theta;

  }


  void PiedPlayerInputComponent::HandleFiring(Level & level, float angle)
  {

    if (currentFireCD <= 0) 
    {
      float instX = getGameObject().x() + getGameObject().w() / 2;
      float instY = getGameObject().y() + getGameObject().h() / 2;
      float xOffset = ((getGameObject().w() / 2) + playerScript.getBulletSize() * 1.3f) * cos(angle * (3.14f / 180.0f));
      float yOffset = ((getGameObject().h() / 2) + playerScript.getBulletSize() * 1.3f) * sin(angle * (3.14f / 180.0f));
      level.addObject(make_shared<PiedBullet>((int)instX + xOffset, (int)instY + yOffset, playerScript.getBulletSize(), playerScript.getBulletSize(), angle, ignores));

      SoundManager::getInstance().playSoundEffect(0);

      currentFireCD = playerScript.getFiringCD();
    }
  }



