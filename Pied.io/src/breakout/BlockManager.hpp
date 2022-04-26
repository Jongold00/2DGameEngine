#ifndef BLOCK_MANAGER_HPP
#define BLOCK_MANAGER_HPP

#include <base/SDLGraphicsProgram.hpp>
#include "base/SDL_DEBUG.hpp"
#include <map>
#include <string>
#include "BreakoutBlock.hpp"
#include "base/Level.hpp"
#include <vector>
#include <fstream>



using namespace std;

/**
 * @file BlockManager.hpp
 * @brief Header for BlockManager class
 */

// instance of class Block
class BreakoutBlock;

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

    int currentLevel = 1;

    int textureHeight = 32; // our block texture is 32 pixels tall
    int textureWidth = 64;  // and 64 pixels wide

    int blockOffsetX;
    int blockOffsetY;

    // returns a BlockManager
    static BlockManager &getInstance();

    std::shared_ptr<Level> loadLevelFromPath(const std::string & filename, std::shared_ptr<Level> level);

    void writeToNewFile(Level* level);

    int calcNumRows(Level* level);

    void loadNextLevel();


};

#endif
