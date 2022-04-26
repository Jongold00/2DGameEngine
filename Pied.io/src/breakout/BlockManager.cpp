#include "BlockManager.hpp"


using namespace std;

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
 * @brief loads a level from a given file path
 * 
 * @param filename, type const & string
 * @param w, type int
 * @param h, type int
 */
std::shared_ptr<Level> BlockManager::loadLevelFromPath(const std::string & filename, std::shared_ptr<Level> level)
{

  std::ifstream infile(filename);

  size_t r;
  size_t c;

  string currLine;
  getline(infile, currLine);

  r = stoi(currLine.substr(2));

  getline(infile, currLine);

  c = stoi(currLine.substr(2));

  textureWidth = level->w() / (c + 1);
  textureHeight = level->h() / (r + 12);


  int xPad = textureWidth / 2;
  int yPad = textureHeight;


  while(getline(infile, currLine)) 
  {

    xPad = textureWidth / 2;


    for (auto it = currLine.begin(); it < currLine.end(); it++)
    {
      if (*it == '.') 
      {
        xPad += textureWidth;

      }

      else if (*it == 'X')
      {
        level->addObject(std::make_shared<BreakoutBlock>(xPad, yPad, textureWidth, textureHeight));
        xPad += textureWidth;
      }
      else if (*it == ' ')
      {

      }
      else
      {
        std::cout << "ERROR WHILE READING IN FILE, INVALID CHAR" << std::endl;
      }
    }

    yPad += BlockManager::getInstance().textureHeight;

  }
  return level;
}


void BlockManager::writeToNewFile(Level* level)
{
  std::string newFileName;
  std::cout << "CHOOSE A NAME FOR YOUR NEW LEVEL" << std::endl;
  std::cout << std::endl;
  std::getline(cin, newFileName);
  std::ofstream tempFile;
  tempFile.open(getResourcePath("breakout/levels") + newFileName + ".txt", ios::out);

  std::vector<std::shared_ptr<GameObject>> level_objects = level->getObjects();
  
  int num_rows = calcNumRows(level);
  int num_cols = (level->w() / textureWidth) - 1;

  string rows_line = "r:" + std::to_string(num_rows);
  string cols_line = "c:" + std::to_string(num_cols);
 


  tempFile << rows_line << std::endl;
  tempFile << cols_line << std::endl;

  

  map<pair<int,int>, char> go_positions;

  for (std::shared_ptr<GameObject> go : level_objects) {

    if (go->tag() == BreakoutBlock::BLOCK_TAG) {      

      char go_char = 'X';
      int x_index = round((go->x() - textureWidth / 2) / textureWidth);
      int y_index = round((go->y() - textureHeight) / textureHeight);


      pair<int, int> coords = make_pair(x_index, y_index);
      go_positions.insert({coords, go_char});

    }

    
  }

  for (int r = 0; r < num_rows; r++) {
    for (int c = 0; c < num_cols; c++) {
      pair<int, int> coords = make_pair(c, r);
      if (go_positions.find(coords) != go_positions.end()) {
        tempFile << go_positions[coords] << ' ';
      }
      else {
        tempFile << ". ";
      }
    
    }
      tempFile << std::endl;
  }
  
  
  tempFile.close();
  SDL_Event sdlevent;
  sdlevent.type = SDL_QUIT;

  SDL_PushEvent(&sdlevent);

}

void
BlockManager::loadNextLevel()
{
  if (currentLevel < 3) {
    currentLevel++;
    std::shared_ptr<Level> level = std::make_shared<Level>(900, 600);
    //loadLevelFromPath("./res/breakout/levels/level" + (std::string)currentLevel + ".txt", level);
  }
  
  
}


int BlockManager::calcNumRows(Level* level) {
  std::vector<std::shared_ptr<GameObject>> level_objects = level->getObjects();
  int lowestH = 0;
  for (std::shared_ptr<GameObject> go : level_objects) {
    if (go->tag() == BreakoutBlock::BLOCK_TAG) {
      if (go->y() > lowestH) {
        lowestH = go->y();
      }
    } 
  }
  return (lowestH / textureHeight);
}

