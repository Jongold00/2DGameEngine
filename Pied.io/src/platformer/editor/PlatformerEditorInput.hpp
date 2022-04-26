#ifndef PLATFORMER_EDITOR_INPUT
#define PLATFORMER_EDITOR_INPUT


#include <base/Component.hpp>
#include <base/GameObject.hpp>
#include <base/InputManager.hpp>
#include "../Player.hpp"
#include "../PlatformerBlock.hpp"
#include "../Collectable.hpp"
#include "../Goal.hpp"
#include "../Enemy.hpp"


class PlatformerEditorInputComponent: public GenericComponent {
public:

  PlatformerEditorInputComponent(GameObject & gameObject):
    GenericComponent(gameObject)
  {

  }
  virtual void update(Level & level) override
  {
    if (InputManager::getInstance().isMousePressed(SDL_BUTTON_LEFT)) 
    {
      shared_ptr<GameObject> to_inst;
      int xMouse, yMouse;
      SDL_GetMouseState(&xMouse, &yMouse);



      std::shared_ptr<GameObject> go = getObjectAtMouseCoords(level, xMouse, yMouse);
      if (go != 0) {
          return;
      }
    
      xMouse = round(xMouse / LevelLoader::textureWidth);
      xMouse *= LevelLoader::textureWidth;
      yMouse = round(yMouse / LevelLoader::textureHeight);
      yMouse *= LevelLoader::textureHeight;

      if (InputManager::getInstance().isKeyDown(SDLK_1)) 
      {
          to_inst = make_shared<Player>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight);
      }

      if (InputManager::getInstance().isKeyDown(SDLK_2)) 
      {
          to_inst = make_shared<PlatformerBlock>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight);
      }

      if (InputManager::getInstance().isKeyDown(SDLK_3)) 
      {
          to_inst = make_shared<Goal>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight);
      }

      if (InputManager::getInstance().isKeyDown(SDLK_4)) 
      {
          to_inst = make_shared<Collectable>(xMouse, yMouse, LevelLoader::textureWidth, LevelLoader::textureHeight);
      }

      if (InputManager::getInstance().isKeyDown(SDLK_5)) 
      {
          to_inst = make_shared<Enemy>(xMouse, yMouse, xMouse, yMouse - (int)(1.5f * LevelLoader::textureHeight), LevelLoader::textureWidth, LevelLoader::textureHeight);
      }

        
      if (to_inst == NULL) {
          return;
      }
      level.addObject(to_inst);

        
    }

    if (InputManager::getInstance().isMousePressed(SDL_BUTTON_RIGHT))
    {
      int xMouse, yMouse;
      SDL_GetMouseState(&xMouse, &yMouse);

      std::shared_ptr<GameObject> go = getObjectAtMouseCoords(level, xMouse, yMouse);
      if (go != 0) {
        level.removeObject(go);
      }
    }

    if (InputManager::getInstance().isKeyPressed(SDLK_s)) 
    {
      LevelLoader::writeToNewFile(&level);
    }
    
    
  }

  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override {

  }
  

  std::shared_ptr<GameObject> getObjectAtMouseCoords(Level & level, int x, int y) 
  {
    std::shared_ptr<GameObject> go = level.checkCoords(x, y);
    return go;
  }


private:
};


class PlatformerEditorInputManager: public GameObject {
  public:

    PlatformerEditorInputManager() : GameObject(0, 0, 0, 0, PLATFORMER_INPUT_TAG)
    {
      addGenericCompenent(std::make_shared<PlatformerEditorInputComponent>(*this));
    }

    static const int PLATFORMER_INPUT_TAG = 101;
};








#endif


		