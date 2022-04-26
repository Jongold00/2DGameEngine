#include "PiedTimerComponent.hpp"
#include "PiedGameStateManager.hpp"
#include "PiedBoss.hpp"

PiedTimer::PiedTimer(GameObject & go, bool countUp):
GenericComponent(go)
{
    milliseconds = 0;
    seconds = 0;
    minutes = 3;
    goUp = countUp;
}

void PiedTimer::countUp(){

    milliseconds++;
    if(milliseconds % 60 == 0){

        seconds ++;
        milliseconds = 0;
    }
    if(seconds > 0 && seconds % 60 == 0){

        minutes ++;
        seconds = 0;
    }

}

void PiedTimer::countDown(){

  

    int counterseconds = 60;

    milliseconds++;
    if(milliseconds % 60 == 0){

        counterseconds ++;
        if(seconds > 0){
        seconds --;
        }
        milliseconds = 0;
    }

     if(counterseconds > 0 && counterseconds % 60 == 0 && seconds <= 0){

        if(minutes > 0){
        minutes --;
        
        seconds = 59;
        counterseconds = 0;
        }
    }

}

void
PiedTimer::update(Level & level)
{
    if(!PiedGameStateManager::getInstance().isGameOver && (minutes > 0 || seconds > 0)){

        
          
    if(goUp){
        countUp();
    }
    else{
        countDown();
    }
    }
    else if (!PiedGameStateManager::getInstance().isGameOver && minutes == 0 && seconds == 0 && !PiedGameStateManager::getInstance().bossSpawned){

            level.addObject(make_shared<PiedBoss>(level.w() / 3, level.h() / 3, 100, 100));
            PiedGameStateManager::getInstance().bossSpawned = true;
    }
    
    
}

void renderMessage(int x, int y, std::string text, SDL_Renderer * gRenderer) 
  {

    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *messageTex = ResourceManager::getInstance().renderText(text, "breakout/sample.ttf", color, 50, false, gRenderer);
    
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

 void PiedTimer::render(SDL_Renderer * gRenderer, std::shared_ptr<GameObject> cam){
     
     string sec;

    if(seconds < 10){
        sec = "0" + std::to_string(seconds);
    }
    else{

        sec = std::to_string(seconds);
        
    }

   string message = "Time til boss  " + std::to_string(minutes) + ":" + sec;

    


    renderMessage(300,25,message, gRenderer);
    //std::cout << "min:sec:msec " << minutes << ":" << seconds << ":" << milliseconds << ":"<< std::endl;




 }
