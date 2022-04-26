#ifndef PIED_BULLET_HPP
#define PIED_BULLET_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "PiedPlayerInput.hpp"
#include "base/RemoveSelfOnCollideComponent.hpp"
#include <cmath>


class PiedBullet : public GameObject 
{
    private:
        float speed;
        float damage;
        
    public:

        PiedBullet(int x, int y, int w, int h, float angle, vector<int> ignores);
        ~PiedBullet() = default;

        static const int BULLET_TAG = 1;

        // removes collectable from a level
    virtual void death(Level & level, std::shared_ptr<GameObject> obj) override;

    void update(Level & level) override; //!< Update the object.

};

#endif