#ifndef LEVEL_LOADER_HPP
#define LEVEL_LOADER_HPP

#include <SDL.h>
#include "SDL_DEBUG.hpp"
#include <map>
#include <string>
#include "ResourceManager.hpp"
#include <vector>
#include <fstream>
#include "Block.hpp"
#include "Player.hpp"
#include "base/Level.hpp"

using namespace std;

/**
 * @brief Class LevelLoader
 *
 * static class that loads levels from .txt files
 * 
 * Public members:
 *
 * vector of blocks
 *
 * int height and width of texture of block,
 *
 */

class Block;

class Player; 

class LevelLoader
{
private:
    LevelLoader() = delete; // static class
    ~LevelLoader() = delete; // static class
    LevelLoader(LevelLoader const &) = delete;   // Avoid copy constructor.
    void operator=(LevelLoader const &) = delete; // Don't allow copy assignment.
    LevelLoader(LevelLoader &&) = delete;        // Avoid move constructor.
    void operator=(LevelLoader &&) = delete;      // Don't allow move assignment.


public:

    inline static vector<Block> blocks;

    inline static Player* player;

    inline static int textureHeight; // the height of a grid square, scaling with screen size
    inline static int textureWidth; // the width of a grid square, scaling with screen size
    inline static int PlayerInitX; // the x coordinate of player's spawn
    inline static int PlayerInitY; // the y coordinate of player's spawn

    inline static int w; // the width of the screen
    inline static int h; // the height of the screen

    // returns a BlockManager
    static LevelLoader &getInstance();

    static Level* loadLevelFromPath(const std::string & filename);

    static void writeToNewFile(Level* level);

    inline static vector<string> level_paths;

    static string getNextLevelPath();
    static string getCurrentLevelPath();

    inline static long long unsigned int currentLevel = 0;

    inline static SDL_Renderer * renderer;
};

#endif
