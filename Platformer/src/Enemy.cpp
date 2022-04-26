
#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include "base/PatrolComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"

/**
 * @brief Construct a new Enemy:: Enemy object
 * 
 * @param x: type int
 * @param y: type int
 * @param px: type int
 * @param py: type int
 * @param w: type int
 * @param h: type int
 */
Enemy::Enemy(int x, int y, int px, int py, int w, int h): GameObject(x, y, w, h, 4)
{

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));

    Src.x = 0;
    Src.y = 0;
    Src.w = 46;
    Src.h = 30;



    this->tex = ResourceManager::getInstance().getTexture("Flying (46x30).png");
    std::pair<SDL_Texture*, int> fruit = make_pair(tex, 7);

    map<std::string, std::pair<SDL_Texture *, int>> anims;

    // THESE ARE THE NAMES OF THE ANIMS
    
    // if you want to set an anim, call RenderComponent->setActiveAnim(string nameOfAnim) for example setActiveAnim("run")

    anims.insert({"idle", fruit});


    setRenderCompenent(std::make_shared<SpriteRenderComponent>(*this, Src, anims));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 0));
    addGenericCompenent(std::make_shared<PatrolComponent>(*this, px, py - 4, 1.0f));
    


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

