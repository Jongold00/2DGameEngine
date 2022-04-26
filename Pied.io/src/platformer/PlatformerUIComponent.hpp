#ifndef PLATFORMER_UI_COMPONENT
#define PLATFORMER_UI_COMPONENT

#include <base/Component.hpp>
#include <base/GameObject.hpp>




class PlatformerUIComponent: public GenericComponent {
public:

  PlatformerUIComponent(GameObject & gameObject):
    GenericComponent(gameObject)
  {
      score_text = "Score_text";
  }
  
  virtual void update(Level & level) override
  {
    score_text = "Score:" + std::to_string(GameStateManager::getInstance().score);
  }

 virtual void render(SDL_Renderer * gRenderer) override {

   if(GameStateManager::getInstance().levelIsOver){


    renderMessage(500,500, GameStateManager::getInstance().endMessage, gRenderer);


   }
   if (GameStateManager::getInstance().gameIsOver)
   {
     renderMessage(500, 500, GameStateManager::getInstance().endMessage, gRenderer);
   }

   renderMessage(20,20, score_text, gRenderer);

 }


  void renderMessage(int x, int y, std::string text, SDL_Renderer * gRenderer) 
  {

    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *messageTex = ResourceManager::getInstance().renderText(text, "platformer/sample.ttf", color, 50, false, gRenderer);
    
    if (messageTex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    

    SDL_Rect messagePos;
    SDL_QueryTexture(messageTex, NULL, NULL, &messagePos.w, &messagePos.h);
    messagePos.x = x;
    messagePos.y = y;
    SDL_RenderCopy(gRenderer, messageTex, NULL, &messagePos);

  }

  std::string score_text;


private:

};

class PlatformerUIManager: public GameObject {
  public:

    PlatformerUIManager() : GameObject(0, 0, 0, 0, UI_TAG)
    {
      addGenericCompenent(std::make_shared<PlatformerUIComponent>(*this));
    }

    static const int UI_TAG = 100;

    virtual void render(SDL_Renderer * renderer) override {

      for (auto genericComponent: mGenericComponents) {
        genericComponent->render(renderer);
      }
  }

};

#endif