#ifndef BREAKOUT_EDITOR_INPUT_COMPONENT
#define BREAKOUT_EDITOR_INPUT_COMPONENT


#include <base/Component.hpp>
#include <base/GameObject.hpp>
#include <base/InputManager.hpp>
#include <breakout/BlockManager.hpp>


class BreakoutEditorInputComponent: public GenericComponent {
public:

  BreakoutEditorInputComponent(GameObject & gameObject):
    GenericComponent(gameObject)
  {

  }
  
  virtual void update(Level & level) override
  {
    if (InputManager::getInstance().isMousePressed(SDL_BUTTON_LEFT)) 
    {
      int xMouse, yMouse;
      SDL_GetMouseState(&xMouse, &yMouse);



      std::shared_ptr<GameObject> go = getObjectAtMouseCoords(level, xMouse, yMouse);
      if (go != 0) {
        return;
      }
      
      xMouse += BlockManager::getInstance().textureWidth / 2;
      xMouse = round(xMouse / BlockManager::getInstance().textureWidth);
      xMouse *= BlockManager::getInstance().textureWidth;
      xMouse -= BlockManager::getInstance().textureWidth / 2;
      yMouse = round(yMouse / BlockManager::getInstance().textureHeight);
      yMouse *= BlockManager::getInstance().textureHeight;




      level.addObject(std::make_shared<BreakoutBlock>(xMouse, yMouse, BlockManager::getInstance().textureWidth, BlockManager::getInstance().textureHeight));
    }

    if (InputManager::getInstance().isMousePressed(SDL_BUTTON_RIGHT))
    {
      int xMouse, yMouse;
      SDL_GetMouseState(&xMouse, &yMouse);

      std::shared_ptr<GameObject> go = getObjectAtMouseCoords(level, xMouse, yMouse);
      if (go != 0 && go->tag() == 2) {
        level.removeObject(go);
      }
    }

    if (InputManager::getInstance().isKeyPressed(SDLK_s)) 
    {
      BlockManager::getInstance().writeToNewFile(&level);
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


class BreakoutEditorInputManager: public GameObject {
  public:

    BreakoutEditorInputManager() : GameObject(0, 0, 0, 0, BREAKOUT_EDITOR_INPUT_TAG)
    {

      addGenericCompenent(std::make_shared<BreakoutEditorInputComponent>(*this));
    }

    static const int BREAKOUT_EDITOR_INPUT_TAG = 101;
};








#endif


		