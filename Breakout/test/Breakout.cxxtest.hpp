#include <cxxtest/TestSuite.h>
#include "SDLGraphicsProgram.hpp"
#include "BlockManager.hpp"
#include "GameStateManager.hpp"
#include "Ball.hpp"
#include "Block.hpp"

class BreakoutTestSuite: public CxxTest::TestSuite
{
public:
    const float EPSILON = 0.001f;
    const int ROWS = 2;
    const int COLS = 2;
    const int w = 1080;
    const int h = 920;

    const int texWidth = w / (ROWS + 4);
    const int texHeight = h / (COLS + 12);

    void testBlockManager() 
    {
        BlockManager::getInstance().startUp(ROWS, COLS, w, h);

        
        TS_ASSERT(BlockManager::getInstance().CheckHitboxes(texWidth * 1.5, texHeight * 1.5));
        TS_ASSERT(BlockManager::getInstance().CheckHitboxes((ROWS * texWidth) + texWidth/2, (texHeight * COLS) + texHeight/2));
        TS_ASSERT(!BlockManager::getInstance().CheckHitboxes(0, 0));
        

        BlockManager::getInstance().DestroyBlocks();
        
        size_t blocks_size = BlockManager::getInstance().blocks.size();

        TS_ASSERT_EQUALS(blocks_size, (long long unsigned int)0);

        BlockManager::getInstance().shutDown();

    }

    void testGameStateManager()
    {
        GameStateManager::getInstance().startUp();
        TS_ASSERT_EQUALS(GameStateManager::getInstance().lives, 3);
        TS_ASSERT_EQUALS(GameStateManager::getInstance().score, 0);

        GameStateManager::getInstance().updateScore(60);
        GameStateManager::getInstance().updateLives();

        TS_ASSERT_EQUALS(GameStateManager::getInstance().lives, 2);
        TS_ASSERT_EQUALS(GameStateManager::getInstance().score, 60);

        GameStateManager::getInstance().updateScore(60);
        GameStateManager::getInstance().updateLives();

        TS_ASSERT_EQUALS(GameStateManager::getInstance().lives, 1);
        TS_ASSERT_EQUALS(GameStateManager::getInstance().score, 120);

    }

    void testBall()
    {
        Ball* b = new Ball();
        b->x += b->vel.x;
        b->y += b->vel.y;

        TS_ASSERT_EQUALS(b->x, 3);
        TS_ASSERT_EQUALS(b->y, 4);

        Ball* b2 = new Ball(6, 9);
        b2->x += b2->vel.x;
        b2->y += b2->vel.y;

        TS_ASSERT_EQUALS(b2->x, 9);
        TS_ASSERT_EQUALS(b2->y, 13);





    }
    

};
