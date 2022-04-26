#include "LevelLoader.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Goal.hpp"
#include "Collectable.hpp"
#include "Enemy.hpp"

/**
 * @brief loads the level from a given file path
 * 
 * @param filename 
 * @param w 
 * @param h 
 * @return Level* 
 */
Level* LevelLoader::loadLevelFromPath(const std::string & filename)
{
  std::cout << "loading level from path: " << filename << std::endl;
  // file IO code adopted from sample on Stack Overflow
  // https://stackoverflow.com/questions/20739453/using-getline-with-file-input-in-c
  std::ifstream infile(filename);


  Level* level = new Level(w, h);


  // dimensions of the level grid
  size_t r;
  size_t c;

  string currLine;
  getline(infile, currLine);

  r = stoi(currLine.substr(2));

  getline(infile, currLine);

  c = stoi(currLine.substr(2));


  // scales the size of all textures to fit the screen
  LevelLoader::textureWidth = w / c;
  LevelLoader::textureHeight = h / r;

  std::cout << textureHeight<< " " << textureWidth << std::endl;

  int xPad = 0;
  int yPad = 0;


  while(getline(infile, currLine)) 
  {

    xPad = 0;


    for (auto it = currLine.begin(); it < currLine.end(); it++)
    {
      // empty space
      if (*it == '.') 
      {
        
        xPad += textureWidth;
       
        
      }

      // block
      else if (*it == 'X')
      {
        level->addObject(std::make_shared<Block>(xPad, yPad, textureWidth, textureHeight));

        xPad += textureWidth;
      }

      else if (*it == ' ')
      {
        continue;
      }
      
      // player spawn
      else if (*it == 'P')
      {
        level->addObject(std::make_shared<Player>(xPad, yPad, textureWidth, textureHeight));
        PlayerInitX = xPad;
        PlayerInitY = yPad;
        xPad += textureWidth;
      }

      // goal
      else if (*it == 'G')
      {
        level->addObject(std::make_shared<Goal>(xPad, yPad, textureWidth, textureHeight));
        xPad += textureWidth;
      }

      // collectable
      else if (*it == 'C')
      {
        level->addObject(std::make_shared<Collectable>(xPad, yPad, textureWidth, textureHeight));
        xPad += textureWidth;

      }

      // enemy
      else if (*it == 'E')
      {
        level->addObject(std::make_shared<Enemy>(xPad, yPad, xPad, yPad - (1.5 * textureWidth), textureWidth, textureHeight));
        xPad += textureWidth;
      }
        
      // error message if invalid character in file
      else 
      {
        xPad += textureWidth;
        std::cout << "ERROR WHILE READING IN FILE, INVALID CHAR" << "\n char is: " << *it << std::endl;
      }

    }

    yPad += textureHeight;

  }
  level->render(renderer);
  return level;
}

void LevelLoader::writeToNewFile(Level* level)
{
  string newFileName;
  std::cout << "CHOOSE A NAME FOR YOUR NEW LEVEL" << std::endl;
  std::cout << std::endl;
  std::getline(cin, newFileName);
  ofstream tempFile;
  tempFile.open("./res/levels/" + newFileName + ".txt", ios::out);

  std::vector<std::shared_ptr<GameObject>> level_objects = level->getObjects();
  
  
  string rows_line = "r:" + std::to_string(level->h() / textureHeight);
  string cols_line = "c:" + std::to_string(level->w() / textureWidth);
 

  std::cout << rows_line << std::endl;

  tempFile << rows_line << std::endl;
  tempFile << cols_line << std::endl;

  

  map<pair<int,int>, char> go_positions;

  for (std::shared_ptr<GameObject> go : level_objects) {

    int x_index = round(go->x() / textureWidth);
    int y_index = round(go->y() / textureHeight);
    char go_char;

    switch (go->tag())
    {
    case 0:
      go_char = 'P';
      break;

    case 1:
      go_char = 'X';
      break;

    case 2:
      go_char = 'G';
      break;

    case 3:
      go_char = 'C';
      break;

    case 4:
      go_char = 'E';
      break;        
    
    default:
      break;
    }

    pair<int, int> coords = make_pair(x_index, y_index);
    go_positions.insert({coords, go_char});
    
  }

  for (int r = 0; r < (level->h() / textureHeight); r++) {
    for (int c = 0; c < (level->w() / textureWidth); c++) {

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

}

std::string
LevelLoader::getNextLevelPath()
{
  currentLevel++;
  if (currentLevel >= level_paths.size()) 
  {
    return "";
  }
  else
  {
    return level_paths[currentLevel];
  }

}

std::string
LevelLoader::getCurrentLevelPath()
{
  return level_paths[currentLevel];
}

