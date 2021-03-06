#ifndef BASE_LEVEL
#define BASE_LEVEL

#include "base/GameObject.hpp"
#include <SDL.h>
#include <memory>
#include <vector>

//! \brief A level in the game.  Essentially mannages a collection of game
//! objects, and does some collision detection.
class Level {
public:

  Level(int w, int h);

  inline int w() const { return mW; }
  inline int h() const { return mH; }

  void addObject(std::shared_ptr<GameObject> object); //!< Set an object to be added.
  void removeObject(std::shared_ptr<GameObject> object); //!< Set an object to be removed.
  void removeAllObjects(); //!< Set an object to be removed.

  bool getCollisions(const GameObject & obj, std::vector<std::shared_ptr<GameObject>> & objects) const; //!< Get objects colliding with a given object.
  bool getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>> & objects) const; //!< Get objects colliding with a given point.

  void update(bool editorMode); //!< Update the objects in the level.
  void render(SDL_Renderer * renderer); //!< Render the level.
  void endGameWon(SDL_Renderer * renderer);
  std::shared_ptr<GameObject> checkCoords(int x, int y);

  std::vector<std::shared_ptr<GameObject>> getObjects();

private:
  
  Level(const Level &) = delete;
  void operator=(Level const&) = delete;



  int mW, mH;
  std::vector<std::shared_ptr<GameObject>> mObjects;

  std::vector<std::shared_ptr<GameObject>> mObjectsToAdd;
  std::vector<std::shared_ptr<GameObject>> mObjectsToRemove;


};

#endif
