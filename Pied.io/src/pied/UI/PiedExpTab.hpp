#ifndef PIED_EXP_TAB_HPP
#define PIED_EXP_TAB_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RenderComponent.hpp"
#include "base/RectRenderComponent.hpp"
#include "../PiedPlayer.hpp"


class PiedExpTracker;

/**
 * @brief 
 * 
 */
class PiedExpTab: public GameObject
{
    private:
        int xOffset = -450;
        int yOffset = 100;

        shared_ptr<GameObject> playerRef = nullptr;
        shared_ptr<PiedExpTracker> expScript = nullptr;

    public:
    PiedExpTab(int x, int y, int w, int h, shared_ptr<PiedExpTracker> exp);
    ~PiedExpTab() = default;

    virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override;
    virtual void update(Level & level) override;
    static const int EXP_TAB_TAG = 73;
};

#endif