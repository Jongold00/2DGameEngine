#include "ResourceManager.hpp"

/**
 * @file ResourceManager.cpp
 * @brief Handles asset loading and moderation
 */

/**
 * @brief Creates new instance of ResourceManager
 * 
 * @return ResourceManager& 
 */
ResourceManager & ResourceManager::getInstance()
{
  static ResourceManager * instance = new ResourceManager();
  return *instance;
}

/**
 * @brief Starts up rendering
 * 
 * @param renderer, type SDL_Renderer* 
 */
void ResourceManager::startUp(SDL_Renderer * renderer)
{
  renderer_ = renderer;
  loadLevel("./res/level1.txt");
  loadLevel("./res/level2.txt");
  loadLevel("./res/level3.txt");

}

/**
 * @brief shuts down rendering
 * 
 */
void ResourceManager::shutDown()
{

  for (auto & e: textures_) {
    SDL_DestroyTexture(e.second);
  }

  for (auto & e: textures_english) {
    SDL_DestroyTexture(e.second);
  }

  for (auto & e: textures_hindi) {
    SDL_DestroyTexture(e.second);
  }

  for (auto & e: music_) {
    Mix_FreeMusic(e.second);
  }

  for (auto & e: sound_effects_) {
    Mix_FreeChunk(e.second);
  }

}



/**
 * @brief Gets texture from file
 * 
 * @param filename, type const string &
 * @return SDL_Texture* 
 */
SDL_Texture * ResourceManager::getTexture(const std::string & filename)
{
  const std::string resource_filename = "./res/" + filename;

  auto it = textures_.find(resource_filename);


  if (it != textures_.end()) {
    return it->second;
  }

  else {
    SDL_Surface *spriteSheet = SDL_LoadBMP(resource_filename.c_str());
    if (spriteSheet == nullptr){
      SDL_Log("Failed to allocate surface");
      return nullptr;
    }


    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, spriteSheet);

    textures_.insert(make_pair(resource_filename, texture));
    return texture;
  }
}

/**
 * @brief Loads in level
 * 
 * @param filename, type string
 */
void ResourceManager::loadLevel(string filename) 
{
  level_paths.push_back(filename);
}

/**
 * @brief returns current level
 * 
 * @return string& (the current level)
 */
string & ResourceManager::getCurrentLevel()
{
  std::cout << "current level: " << GameStateManager::getInstance().getCurrentLevel() << std::endl;
  return level_paths[GameStateManager::getInstance().getCurrentLevel()];
}

/**
 * @brief returns the number of levels
 * 
 * @return int (number of levels)
 */
int ResourceManager::getNumLevels()
{
  return level_paths.size();
}

/**
 * @brief finds a sound effect as a file
 * 
 * @param filename, type const string &
 * @return Mix_Chunk* 
 */
Mix_Chunk * ResourceManager::getSoundEffect(const std::string & filename)
{
  const std::string resource_filename = "./res/" + filename;

  auto it = sound_effects_.find(resource_filename);


  if (it != sound_effects_.end()) {
    return it->second;
  }

  else {

    Mix_Chunk * sound_effect = Mix_LoadWAV(resource_filename.c_str());

    sound_effects_.insert(make_pair(resource_filename, sound_effect));

    return sound_effect;
  }
}

/**
 * @brief finds music from file
 * 
 * @param filename, type const string &
 * @return Mix_Music* 
 */
Mix_Music * ResourceManager::getMusic(const std::string & filename)
{
  const std::string resource_filename = "./res/" + filename;

  auto it = music_.find(resource_filename);


  if (it != music_.end()) {
    return it->second;
  }

  else {

    Mix_Music * music = Mix_LoadMUS(resource_filename.c_str());

    music_.insert(make_pair(resource_filename, music));

    return music;
  }
}





/**
 * @brief gives error message
 * 
 * @param os, type ostream &
 * @param msg, type const string
 */
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
} 

/**
 * @brief generates text from message info
 * 
 * @param message, type const string &
 * @param fontFile, type const string &
 * @param color, type SDL_Color
 * @param fontSize, type int
 * @param langChange, type bool
 * @param renderer, type SDL_Renderer*
 * @return SDL_Texture* 
 */
SDL_Texture* ResourceManager::renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, bool langChange, SDL_Renderer *renderer)
{
  std::string resource_filename;

  if (TTF_Init() != 0) {
	  logSDLError(std::cout, "TTF_Init");
	  SDL_Quit();
  }
  if (langChange) {
  resource_filename = "./res/Ananda Akchyar.ttf";

  auto it = textures_hindi.find(message);

  if (it != textures_hindi.end()) {
    return it->second;
  }

  }
  else{
    resource_filename = "./res/" + fontFile;


    auto it = textures_english.find(message);

  if (it != textures_english.end()) {
    return it->second;
  }
  }

  



	/**
	 * @brief opens the font
	 * 
	 */
	TTF_Font *font = TTF_OpenFont(resource_filename.c_str(), fontSize);
	if (font == nullptr){
		logSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}	
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
  /**
   * @brief renders to a surface and loads surface
   * 
   */
	SDL_Surface *surf = TTF_RenderUTF8_Solid(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return nullptr; 
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		logSDLError(std::cout, "CreateTexture");
	}
  //textures_.insert(make_pair(resource_filename, texture));
	//Clean up the surface and font


    if (langChange) {
  textures_hindi.insert(make_pair(message, texture));
    }
    else{
      textures_english.insert(make_pair(message, texture));
    }
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
  
  
/*
  const std::string resource_filename = "./res/" + fontFile;

  auto it = textures_.find(message);


  if (it != textures_.end()) {
    return it->second;
  }


  

	//Open the font
	TTF_Font *font = TTF_OpenFont(resource_filename.c_str(), fontSize);
	if (font == nullptr){
		logSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}	
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return nullptr; 
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		logSDLError(std::cout, "CreateTexture");
	}
  //textures_.insert(make_pair(resource_filename, texture));
	//Clean up the surface and font
  textures_.insert(make_pair(message, texture));
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;*/
  
}

