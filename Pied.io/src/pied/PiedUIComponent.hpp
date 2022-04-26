#ifndef PIED_UI_COMPONENT
#define PIED_UI_COMPONENT

#include <base/Component.hpp>
#include <base/GameObject.hpp>
#include "PiedTimerComponent.hpp"




 

class PiedUIComponent: public GenericComponent {
public:

  PiedUIComponent(GameObject & gameObject):
    GenericComponent(gameObject)
  {
      score_text = "Score_text";
      lives_text = "Lives:0";
  }
  
  virtual void update(Level & level) override
  {
    score_text = "Score:" + std::to_string(PiedGameStateManager::getInstance().score);
    lives_text = "Lives:" + std::to_string(PiedGameStateManager::getInstance().lives);
    lang = PiedGameStateManager::getInstance().lang;
  }

 virtual void render(SDL_Renderer * gRenderer, std::shared_ptr<GameObject> cam) override {

   if(PiedGameStateManager::getInstance().isGameOver){


    renderMessage(500,500, PiedGameStateManager::getInstance().endMessage, gRenderer);


   }

   renderMessage(20,50, score_text, gRenderer);
   renderMessage(20,100, lives_text, gRenderer);

 }

 


  void renderMessage(int x, int y, std::string text, SDL_Renderer * gRenderer) 
  {

    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *messageTex = ResourceManager::getInstance().renderText(text, "breakout/sample.ttf", color, 50, lang, gRenderer);
    
    if (messageTex == nullptr)
    {
      cout << "null text texture" << endl;
    }
    

    SDL_Rect messagePos;
    SDL_QueryTexture(messageTex, NULL, NULL, &messagePos.w, &messagePos.h);
    messagePos.x = x;
    messagePos.y = y;
    SDL_RenderCopy(gRenderer, messageTex, NULL, &messagePos);
    //std::cout<<"language is: " << lang <<std::endl;
  }

  std::string score_text;
  std::string lives_text;
  bool lang;


private:


};

class PiedUIManager: public GameObject {
  public:

    PiedUIManager() : GameObject(0, 0, 0, 0, UI_TAG)
    {
      addGenericCompenent(std::make_shared<PiedUIComponent>(*this));
      addGenericCompenent(std::make_shared<PiedTimer>(*this, false));
    }

    static const int UI_TAG = 100;

    virtual void render(SDL_Renderer * renderer, std::shared_ptr<GameObject> cam) override {

      for (auto genericComponent: mGenericComponents) {
        genericComponent->render(renderer, cam);
      }
  }

};


#endif