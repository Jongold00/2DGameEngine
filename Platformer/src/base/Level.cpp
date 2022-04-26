#include "base/Level.hpp"
#include <algorithm>
#include <iostream>

Level::Level(int w, int h):
  mW(w),
  mH(h)
{
}

void
Level::addObject(std::shared_ptr<GameObject> object)
{
  mObjectsToAdd.push_back(object);
}

void
Level::removeObject(std::shared_ptr<GameObject> object)
{
  mObjectsToRemove.push_back(object);
  
}

void Level::removeAllObjects(){

  for (auto gameObject: mObjects) {
    
    removeObject(gameObject);
  }

}

bool
Level::getCollisions(const GameObject & obj, std::vector<std::shared_ptr<GameObject>> & objects) const
{
  objects.clear();
  for (auto gameObject: mObjects) {
    if (gameObject.get() != &obj && gameObject->isColliding(obj)) {
      objects.push_back(gameObject);
    }
  }
  return !objects.empty();
}

bool
Level::getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>> & objects) const
{
  objects.clear();
  for (auto gameObject: mObjects) {
    if (gameObject->isColliding(px, py)) {
      objects.push_back(gameObject);
    }
  }
  return !objects.empty();
}

void
Level::update(bool editorMode)
{
  for (auto obj: mObjectsToAdd) {
    mObjects.push_back(obj);
  }
  mObjectsToAdd.clear();
  
  for (auto gameObject: mObjects) {
    if (!editorMode) {
      gameObject->update(*this);
    }
  }
  for (auto gameObject: mObjects) {
    if (!editorMode) {
      gameObject->step(*this);
    }
  }

  for (auto obj: mObjectsToRemove) {
    auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
    if (elem != mObjects.end()) {
      mObjects.erase(elem);
    }
  }
  mObjectsToRemove.clear();
}

void
Level::render(SDL_Renderer * renderer)
{
  //std::cout << "number of objects: " + mObjects.size() << std::endl;
  for (auto gameObject: mObjects) {
    //std::cout << "rendering an object. tag: " + gameObject->tag() << std::endl;
    gameObject->render(renderer);
  }
}

void 
Level::endGameWon(SDL_Renderer * renderer)
{
  
}

std::vector<std::shared_ptr<GameObject>>
Level::getObjects()
{
  return mObjects;
}

std::shared_ptr<GameObject> 
Level::checkCoords(int x, int y)
{
  // base case if nothing -> null ptr
  for(std::shared_ptr<GameObject> currObj : mObjects) {
    if (currObj->x() < x && (currObj->x() + currObj->w()) > x &&
       (currObj->y() < y && (currObj->y() + currObj->h()) > y))
    {
      return currObj;
    }
  }
  return nullptr;

  // loop through mObjects and find their x and y
}