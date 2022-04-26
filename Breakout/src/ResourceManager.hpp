#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL.h>
#include "SDL_DEBUG.hpp"
#include <map>
#include <string>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "GameStateManager.hpp"

using namespace std;

/**
 * @file ResourceManager.hpp
 * @brief Header for ResourceManager class
 */

/**
 * @brief ResourceManager class that controls assets
 * @class ResourceManager
 */

/**
 * A class for managing game resources.  Allows access to resources
 * and makes sure there is only one copy of each resource loaded at a
 * time.
 */
class ResourceManager {
private:

  ResourceManager() = default; // Private Singleton
  ~ResourceManager() = default;
  ResourceManager(ResourceManager const&) = delete; // Avoid copy constructor.
  void operator=(ResourceManager const&) = delete; // Don't allow copy assignment.
  ResourceManager(ResourceManager &&) = delete; // Avoid move constructor.
  void operator=(ResourceManager &&) = delete; // Don't allow move assignment.

public:

  static ResourceManager &getInstance();

  // 'equivalent' to our constructor
  // do anything needed to initialize
  void startUp(SDL_Renderer * renderer);

  // 'equivalent' to our destructor
  // make sure that any allocated resources are freed
  void shutDown();

  // get the texture assosciated with the given filename
  // if the given file has already been loaded, return the already loaded resource
  // otherwise, load the resource from the file, remember it, and return it
  SDL_Texture * getTexture(const std::string & filename);
  Mix_Chunk * getSoundEffect(const std::string & filename);
  Mix_Music * getMusic(const std::string & filename);
  SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, bool langChange, SDL_Renderer *renderer);
  void loadLevel(string filename);
  string & getCurrentLevel(); 
  int getNumLevels();

private:

  SDL_Renderer * renderer_ = nullptr;
  std::map< std::string, SDL_Texture * > textures_;
  std::map< std::string, SDL_Texture * > textures_english;
  std::map< std::string, SDL_Texture * > textures_hindi;
  std::map<std::string, Mix_Chunk * > sound_effects_;
  std::map<std::string, Mix_Music * > music_;
  vector<string> level_paths;

};

#endif
