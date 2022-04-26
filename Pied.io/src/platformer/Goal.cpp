#include "Goal.hpp"


/**
 * @file Goal.cpp
 * @brief Constructs Goal object and checks hitbox
 */

/**
 * @brief Constructor for new Goal:: Goal object
 *
 * @param x: type int
 * @param y: type int
 */
Goal::Goal(int x, int y, int w, int h) : GameObject(x, y, w, h, GOAL_TAG)
{
    SDL_Rect Src;
    Src.x = 0;
    Src.y = 0;
    Src.w = 64;
    Src.h = 64;
    
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    


    this->texture = ResourceManager::getInstance().getTexture("platformer/Goal (Flag Idle)(64x64).png");
    std::pair<SDL_Texture*, int> goal = make_pair(texture, 10);

    map<std::string, std::pair<SDL_Texture *, int>> anims;

    // THESE ARE THE NAMES OF THE ANIMS
    
    // if you want to set an anim, call RenderComponent->setActiveAnim(string nameOfAnim) for example setActiveAnim("run")

    anims.insert({"idle", goal});

    setRenderCompenent(std::make_shared<SpriteRenderComponent>(*this, Src, anims));

    std::shared_ptr<RenderComponent> sprite = renderComponent();
    sprite->setActiveAnim("idle");
    

}

/**
 * @brief Indicates the ending of the game upon collision with player
 * 
 * @param level 
 * @param obj 
 */
void Goal::death(Level & level, std::shared_ptr<GameObject> obj) 
{

  this->isDead = true;
  SoundManager::getInstance().playSoundEffect(2);
  GameStateManager::getInstance().levelComplete();
  std::cout << "game is won" << std::endl;
  
}
