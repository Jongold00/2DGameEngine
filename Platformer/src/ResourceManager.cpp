#include "ResourceManager.hpp"
#include "res-path.hpp"

/**
 * @brief gives resource manager
 * 
 * @return ResourceManager& 
 */
ResourceManager & ResourceManager::getInstance()
{
  static ResourceManager * instance = new ResourceManager();
  return *instance;
}

/**
 * @brief starts up render
 * 
 * @param renderer 
 */
void ResourceManager::startUp(SDL_Renderer * renderer)
{
  renderer_ = renderer;
  std::string resPath = getResourcePath("./res/level1.txt");
  loadLevel(resPath);


}

/**
 * @brief shuts down render
 * 
 */
void ResourceManager::shutDown()
{
  for (auto & e: textures_) {
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
 * @brief gives the texture from a given file path
 * 
 * @param filename 
 * @return SDL_Texture* 
 */
SDL_Texture * ResourceManager::getTexture(const std::string & filename)
{
  std::string resPath = getResourcePath("");
  const std::string resource_filename = resPath + filename;

  auto it = textures_.find(resource_filename);


  if (it != textures_.end()) {
    return it->second;
  }

  else {
    SDL_Surface* spriteSheet = IMG_Load(resource_filename.c_str());
    std::cout << "pointer to surface: " << spriteSheet << std::endl;
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
 * @brief loads a level from a given file
 * 
 * @param filename 
 */
void ResourceManager::loadLevel(string filename) 
{
  level_paths.push_back(filename);
}

/**
 * @brief gives the current level
 * 
 * @return string& 
 */
string & ResourceManager::getCurrentLevel()
{
  std::cout << "current level: " << GameStateManager::getInstance().getCurrentLevel() << std::endl;
  return level_paths[GameStateManager::getInstance().getCurrentLevel()];
}

/**
 * @brief gives the number of levels
 * 
 * @return int 
 */
int ResourceManager::getNumLevels()
{
  return level_paths.size();
}

/**
 * @brief gives a sound effect from a given file
 * 
 * @param filename 
 * @return Mix_Chunk* 
 */
Mix_Chunk * ResourceManager::getSoundEffect(const std::string & filename)
{
  std::string resPath = getResourcePath("");
  const std::string resource_filename = resPath + filename;

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
 * @brief gives music from a given file
 * 
 * @param filename 
 * @return Mix_Music* 
 */
Mix_Music * ResourceManager::getMusic(const std::string & filename)
{
  std::string resPath = getResourcePath("");
  const std::string resource_filename = resPath + filename;

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
 * @brief error message for SDL
 * 
 * @param os 
 * @param msg 
 */
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
} 

SDL_Texture* ResourceManager::renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, bool langChange, SDL_Renderer *renderer)
{

  if (TTF_Init() != 0) {
	  logSDLError(std::cout, "TTF_Init");
	  SDL_Quit();
  }
  if (langChange) {
  const std::string resource_filename = "./res/Ananda Akchyar.ttf";

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
  textures_.insert(make_pair(message, texture));
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
  }
  std::string resPath = getResourcePath("");
  const std::string resource_filename = resPath + fontFile;

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
	return texture;
}

