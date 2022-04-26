
#include "Collectable.hpp"
#include "ResourceManager.hpp"
#include "GameStateManager.hpp"

/**
 * @brief Construct a new Collectable:: Collectable object
 * 
 * @param x: type int
 * @param y: type int
 * @param w: type int
 * @param h: type int
 */
Collectable::Collectable(int x, int y, int w, int h): GameObject(x, y, w, h, 3)
{

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));

    Src.x = 0;
    Src.y = 0;
    Src.w = 32;
    Src.h = 32;



    this->tex = ResourceManager::getInstance().getTexture("Kiwi.png");
    std::pair<SDL_Texture*, int> fruit = make_pair(tex, 17);

    map<std::string, std::pair<SDL_Texture *, int>> anims;

    // THESE ARE THE NAMES OF THE ANIMS
    
    // if you want to set an anim, call RenderComponent->setActiveAnim(string nameOfAnim) for example setActiveAnim("run")



    anims.insert({"idle", fruit});



    setRenderCompenent(std::make_shared<SpriteRenderComponent>(*this, Src, anims));
    


    std::shared_ptr<RenderComponent> sprite = renderComponent();
    sprite->setActiveAnim("idle");

    this->point_value = 1;
    this->x = x;
    this->y = y;

    Dst.x = x;
    Dst.y = y;
    Dst.w = w;
    Dst.h = h;


    hitbox = new Hitbox(Dst.h - 5, Dst.w - 5, x, y);

}

/**
 * @brief removes collectable from level
 * 
 * @param level: type Level&
 * @param obj: type GameObject
 */
void Collectable::death(Level & level, std::shared_ptr<GameObject> obj) 
{

  SoundManager::getInstance().playSoundEffect(1);
  std::cout << "player collected fruit" << std::endl;
  GameStateManager::getInstance().updateScore(this->point_value);
  
  level.removeObject(obj);

  
}

