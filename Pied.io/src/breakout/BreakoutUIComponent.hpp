#ifndef BREAKOUT_UI_COMPONENT
#define BREAKOUT_UI_COMPONENT

#include <base/Component.hpp>
#include <base/GameObject.hpp>




 

class BreakoutUIComponent: public GenericComponent {
public:

  BreakoutUIComponent(GameObject & gameObject):
    GenericComponent(gameObject)
  {
      score_text = "Score_text";
      lives_text = "Lives:0";
  }
  
  virtual void update(Level & level) override
  {
    score_text = "Score:" + std::to_string(BreakoutGameStateManager::getInstance().score);
    lives_text = "Lives:" + std::to_string(BreakoutGameStateManager::getInstance().lives);
    lang = BreakoutGameStateManager::getInstance().lang;
  }

 virtual void render(SDL_Renderer * gRenderer) override {

   if(BreakoutGameStateManager::getInstance().isGameOver){


    renderMessage(500,500, "GAME IS OVER", gRenderer);


   }

   renderMessage(20,300, score_text, gRenderer);
   renderMessage(20,370, lives_text, gRenderer);

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
    std::cout<<"language is: " << lang <<std::endl;
  }

  std::string score_text;
  std::string lives_text;
  bool lang;


private:


};

class BreakoutUIManager: public GameObject {
  public:

    BreakoutUIManager() : GameObject(0, 0, 0, 0, UI_TAG)
    {
      addGenericCompenent(std::make_shared<BreakoutUIComponent>(*this));
    }

    static const int UI_TAG = 100;

    virtual void render(SDL_Renderer * renderer) override {

      for (auto genericComponent: mGenericComponents) {
        genericComponent->render(renderer);
      }
  }

};


#endif