#include "SpawningComponent.hpp"

SpawningParent::SpawningParent(weak_ptr<GameObject> playerPtr) : GameObject(0, 0, 0, 0, 5)
{
    addGenericCompenent(make_shared<SpawningComponent>(*this, playerPtr));
}

SpawningComponent::SpawningComponent(GameObject &gameObject, weak_ptr<GameObject> playerPtr) : 
GenericComponent(gameObject),
mPlayerPtr(playerPtr)
{

}

void SpawningComponent::update(Level &level)
{
    
    int collectable_count = 0;
    int enemies_count = 0;

    for (auto go : level.getObjects())
    {
        if (go->tag() == PiedCollectible::COLLECTABLE_TAG)
        {
            collectable_count++;
        }

        if (go->tag() == PiedEnemy::ENEMY_TAG)
        {
            enemies_count++;
        }
    }



    if (collectable_count < maxCollectables)
    {   
        mWidth = rand() % level.w();
        mHeight = rand() % level.h();
        level.addObject(make_shared<PiedCollectible>(mWidth, mHeight, 50, 50));
    }

    if (enemies_count < maxEnemies)
    {
        mWidth = rand() % level.w();
        mHeight = rand() % level.h();
        level.addObject(make_shared<PiedEnemy>(mWidth, mHeight, 50, 50, mPlayerPtr));
    }

   
    

}