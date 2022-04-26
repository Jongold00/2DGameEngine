#ifndef BLOCK_MANAGER_HPP
#define BLOCK_MANAGER_HPP

#include <SDL.h>
#include "SDL_DEBUG.hpp"
#include <map>
#include <string>
#include "ResourceManager.hpp"
#include <vector>
#include <fstream>

using namespace std;

/**
 * @file BlockManager.hpp
 * @brief Header for BlockManager class
 */

// instance of class Block
class Block;

/**
 * @brief BlockManager class with dimensions and offset
 * @class BlockManager
 *
 * Private members:
 * Default Constructors and Deconstructors
 * Copy and Move functions to be avoided
 *
 * Public members:
 *
 * vector of blocks
 *
 * int height and width of texture of block,
 * blockoffset variables
 *
 */
class BlockManager
{
private:
    BlockManager() = default; // Private Singleton
    ~BlockManager() = default;
    BlockManager(BlockManager const &) = delete;   // Avoid copy constructor.
    void operator=(BlockManager const &) = delete; // Don't allow copy assignment.
    BlockManager(BlockManager &&) = delete;        // Avoid move constructor.
    void operator=(BlockManager &&) = delete;      // Don't allow move assignment.

public:
    vector<Block> blocks;

    int textureHeight = 32; // our block texture is 32 pixels tall
    int textureWidth = 64;  // and 64 pixels wide

    int blockOffsetX;
    int blockOffsetY;

    // returns a BlockManager
    static BlockManager &getInstance();

    void loadLevelFromPath(const std::string & filename, int w, int h);

    // 'equivalent' to our constructor
    // do anything needed to initialize
    void startUp(int rows, int cols, int w, int h);

    // 'equivalent' to our destructor
    // make sure that any allocated resources are freed
    void shutDown();

    // render's blocks using the SDL_Renderer
    void render(SDL_Renderer *gRenderer);

    int GetRemainingBlocks();

    // checks if any boxes are hit and returns that block
    bool CheckHitboxes(int x, int y);

    // returns size of block that is destroyed
    float DestroyBlocks();
};

#endif
