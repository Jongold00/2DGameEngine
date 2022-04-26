#include "PiedExpTab.hpp"

PiedExpTab::PiedExpTab(int x, int y, int w, int h, shared_ptr<PiedExpTracker> exp):
GameObject(x, y, w, h, EXP_TAB_TAG),
expScript(exp)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 519;
    src.h = 351;

    SDL_Texture * tex = ResourceManager::getInstance().getTexture("pied/levelUpUI.png");

    setRenderCompenent(make_shared<TextureRenderComponent>(*this, tex, src));
}

void
PiedExpTab::render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam)
{
    if (expScript->getUnspentPoints() > 0) 
    {

        this->GameObject::render(renderer, cam);

        SDL_Color color = {0, 0, 0, 0};
        string text = "   LEVEL UP";

        SDL_Texture *messageTex = ResourceManager::getInstance().renderText(text, "pied/expui.ttf", color, 25, false, renderer);
        
        if (messageTex == nullptr)
        {
        cout << "null text texture" << endl;
        }
        

        SDL_Rect messagePos;
        messagePos.x = 0;
        messagePos.y = 410;
        messagePos.w = w();
        messagePos.h = h();
        SDL_QueryTexture(messageTex, NULL, NULL, &messagePos.w, &messagePos.h);
        
        SDL_RenderCopy(renderer, messageTex, NULL, &messagePos);


        text = "   POINTS TO SPEND " + to_string(expScript->getUnspentPoints());
        SDL_Texture *pointsLeftText = ResourceManager::getInstance().renderText(text, "pied/expui.ttf", color, 15, false, renderer);
        
        if (messageTex == nullptr)
        {
        cout << "null text texture" << endl;
        }
        

        messagePos.x = 0;
        messagePos.y = 440;
        messagePos.w = w();
        messagePos.h = h();
        SDL_QueryTexture(pointsLeftText, NULL, NULL, &messagePos.w, &messagePos.h);
        
        SDL_RenderCopy(renderer, pointsLeftText, NULL, &messagePos);

        
    }
}

void
PiedExpTab::update(Level & level)
{
  for (auto genericComponent: mGenericComponents) {
    genericComponent->update(level);
  }

  for (auto go: level.getObjects())
  {
      if (go->tag() == PiedPlayer::PIED_PLAYER_TAG)
      {
          playerRef = go;
          setX(go->x() + xOffset);
          setY(go->y() + yOffset);
      }
  }
}