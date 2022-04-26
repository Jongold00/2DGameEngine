#include "Player.hpp"
#include "ResourceManager.hpp"
#include "base/GameWon.hpp"
#include "base/RemoveOnCollideComponent.hpp"

/**
 * @brief custom component for player input
 * 
 */
class PlatformInputComponent: public GenericComponent {
public:


  PlatformInputComponent(GameObject & gameObject, float speed, float jump, float gravity):
    GenericComponent(gameObject),
    mSpeed(speed),
    mJump(jump),
    mGravity(gravity)
  {
  }
  
  virtual void update(Level & level) override
  {
    bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    bool jump = InputManager::getInstance().isKeyPressed(SDLK_UP);
    
    GameObject & gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
    std::shared_ptr<RenderComponent> sprite = gameObject.renderComponent();

    sprite->setActiveAnim("idle");

    // going left
    if (left && !right) {
        pc->setVx(-mSpeed);

    } 
    // going right
    else if (!left && right) {
        pc->setVx(mSpeed);
    }
    // left and right both down, dont go anywhere
    else {
      pc->setVx(0.0f);
    }

    bool onGround = false;

    if (jump) 
    {

      // checking for legal jump 
      std::vector<std::shared_ptr<GameObject>> objects;
      if (level.getCollisions(gameObject.x() + 0.02f * gameObject.w(), gameObject.y() + gameObject.h() + 2.0f, objects)) {
	    for (auto obj: objects) {
	        if (obj->tag() == 1) {
	            onGround = true;
              
	        }
	    }
      }

      if (level.getCollisions(gameObject.x() + 0.98f * gameObject.w(), gameObject.y() + gameObject.h() + 2.0f, objects)) {
	    for (auto obj: objects) {
	        if (obj->tag() == 1) {
	            onGround = true;
              
	        }
	    }
      }

      // jump is successful
      if (onGround) 
      {
        SoundManager::getInstance().playSoundEffect(0);
	    pc->setVy(-mJump);
      pc->isGrounded = false;
      return;
	    
      }
    }

    pc->setVy(std::min(pc->vy() + mGravity, mJump));

  }



private:

  float mSpeed;
  float mJump;
  float mGravity;

};


/**
 * @brief custom collision component for sounds
 * 
 */
class RemoveOnCollisionComponent: public GenericComponent {
public:


   RemoveOnCollisionComponent(GameObject & gameObject, int tag):
    GenericComponent(gameObject),
    mTag(tag)
  {
  }
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override
  {

    if (obj->tag() == mTag) {

    if(mTag == 1){
     SoundManager::getInstance().playSoundEffect(1);
    }
    level.removeObject(obj);

    
  }


  }



private:

float mTag;


};



/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
Player::Player(int x, int y, int w, int h): GameObject(x, y, w * 0.9, h * 0.9, 0)
{
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));

    Src.x = 0;
    Src.y = 0;
    Src.w = 32;
    Src.h = 32;



    this->run_tex = ResourceManager::getInstance().getTexture("Run (32x32).png");
    std::pair<SDL_Texture*, int> run = make_pair(run_tex, 12);


    this->idle_tex = ResourceManager::getInstance().getTexture("idle.png");
    std::pair<SDL_Texture*, int> idle = make_pair(idle_tex, 11);



    this->jump_tex = ResourceManager::getInstance().getTexture("Jump (32x32).png");
    std::pair<SDL_Texture*, int> jump = make_pair(jump_tex, 1);



    this->fall_tex = ResourceManager::getInstance().getTexture("Fall (32x32).png");
    std::pair<SDL_Texture*, int> fall = make_pair(fall_tex, 1);



    map<std::string, std::pair<SDL_Texture *, int>> anims;

    // THESE ARE THE NAMES OF THE ANIMS
    
    // if you want to set an anim, call RenderComponent->setActiveAnim(string nameOfAnim) for example setActiveAnim("run")

    anims.insert({"run", run});
    anims.insert({"idle", idle});
    anims.insert({"jump", jump});
    anims.insert({"fall", fall});




    setRenderCompenent(std::make_shared<SpriteRenderComponent>(*this, Src, anims));

    addGenericCompenent(std::make_shared<PlatformInputComponent>(*this, 5.0f, 10.0f, 0.5f));

    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 3));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 2));

    addGenericCompenent(std::make_shared<GameWon>(*this, 2));


    lookRight = true;

    this->speed = 2;
    this->jumpHeight = 9.0f;
    this->gravityValue = 1.0f;



    width = Dst.w;

    Dst.x = x;
    Dst.y = y;
    Dst.w = w;
    Dst.h = h;

    isGrounded = true;

    xVel = 0;
    yVel = 0;



}

/**
 * @brief updates player within a level
 * 
 * @param level 
 */
void Player::update(Level & level)
{


    GameObject::update(level);

    std::shared_ptr<PhysicsComponent> pc = physicsComponent();
    std::shared_ptr<RenderComponent> sprite = renderComponent();

    if(pc->vx() < 0){

      sprite->flipRender(SDL_FLIP_HORIZONTAL);
      sprite->setActiveAnim("run");
      

    }
    else if(pc->vx() > 0){

      sprite->flipRender(SDL_FLIP_NONE);
      sprite->setActiveAnim("run");
    }
    else{
      sprite->setActiveAnim("idle");
    }

    //pc->isGrounded = true;
      if(!pc->isGrounded && pc->vy() >= 0){

      sprite->setActiveAnim("fall");

    }
    else if(!pc->isGrounded && pc->vy() < 0){

      sprite->setActiveAnim("jump");

    }
   



  
}

/**
 * @brief removes player from a given level
 * 
 * @param level 
 * @param obj 
 */
void Player::death(Level & level, std::shared_ptr<GameObject> obj) 
{

  SoundManager::getInstance().playSoundEffect(3);
  std::cout << "player dies" << std::endl;
  level.removeObject(obj);
  SoundManager::getInstance().shutDown();
  GameStateManager::getInstance().shutDown("You Lose!");


  
}




