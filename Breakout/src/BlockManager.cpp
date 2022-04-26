#include "BlockManager.hpp"
#include "Block.hpp"

/**
 * @file BlockManager.cpp
 * @brief Handles generation and rendering of blocks
 */

/**
 * @brief returns instance of BlockManager
 *
 * @return BlockManager
 */
BlockManager &BlockManager::getInstance()
{
  static BlockManager *instance = new BlockManager();
  return *instance;
}

/**
 * @brief acts as a constructor for blocks
 *
 * @param rows, type int
 * @param cols, type int
 * @param w, type int
 * @param h, type int
 */
void BlockManager::startUp(int rows, int cols, int w, int h)
{
  loadLevelFromPath(ResourceManager::getInstance().getCurrentLevel(), w, h);
  
}

/**
 * @brief loads a level from a given file path
 * 
 * @param filename, type const & string
 * @param w, type int
 * @param h, type int
 */
void BlockManager::loadLevelFromPath(const std::string & filename, int w, int h)
{
  // file IO code adopted from sample on Stack Overflow
  // https://stackoverflow.com/questions/20739453/using-getline-with-file-input-in-c
  std::ifstream infile(filename);

  size_t r;
  size_t c;

  string currLine;
  getline(infile, currLine);

  r = stoi(currLine.substr(5));

  getline(infile, currLine);

  c = stoi(currLine.substr(5));

  textureWidth = w / (c + 4);
  textureHeight = h / (r + 12);

  blockOffsetX = textureWidth / 4;
  blockOffsetY = textureHeight / 4;


  int xPad = textureWidth;
  int yPad = textureHeight;
  Block* newBlock;

  while(getline(infile, currLine)) 
  {
    // std::cout << "line len: " << currLine.length() << std::endl;
    if (currLine.length() > c) 
    {
      std::cout << "ERROR WHILE READING IN FILE, LINE TOO LONG" << std::endl;
    }

    xPad = textureWidth;


    for (auto it = currLine.begin(); it < currLine.end(); it++)
    {
      if (*it == ' ') 
      {
        xPad += blockOffsetX;
        xPad += textureWidth;

      }

      else if (*it == 'x')
      {
        newBlock = new Block(xPad, yPad);
        newBlock->init();
        blocks.push_back(*newBlock); // gets the number of the current block
        xPad += blockOffsetX;
        xPad += textureWidth;
      }
      else
      {
        std::cout << "ERROR WHILE READING IN FILE, INVALID CHAR" << std::endl;
      }
    }

    yPad += BlockManager::getInstance().blockOffsetY;
    yPad += BlockManager::getInstance().textureHeight;

  }




}

/**
 * @brief shuts down the game
 *
 */
void BlockManager::shutDown()
{
  this->blocks.clear();
  this->blocks.shrink_to_fit();
}

/**
 * @brief renders the blocks using SDL_Renderer
 *
 * @param gRenderer, type SDL_Renderer
 */
void BlockManager::render(SDL_Renderer *gRenderer)
{
  for (Block b : this->blocks)
  {
    b.render(gRenderer);
  }
}

/**
 * @brief returns the block hit by the ball
 *
 * @param x, type int
 * @param y, type int
 * @return Block*
 */
bool BlockManager::CheckHitboxes(int x, int y)
{
  for (vector<Block>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
  {
    if ((*it).CheckHitbox(x, y))
    {
      blocks.erase(it);
      return true;
    }
  }

  return false;
}

/**
 * @brief returns the size of the Block destroyed
 *
 * @return float size of block
 */
float BlockManager::DestroyBlocks()
{

  float size = blocks.size();
  blocks.erase(blocks.begin(), blocks.end());
  return size;
  
}

int BlockManager::GetRemainingBlocks() {
  return blocks.size();
}
