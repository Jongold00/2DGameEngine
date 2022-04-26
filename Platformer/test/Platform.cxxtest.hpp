#include <cxxtest/TestSuite.h>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Collectable.hpp>
#include <Goal.hpp>
#include <LevelLoader.hpp>

class PlatformTestSuite: public CxxTest::TestSuite
{
    public:

    void testPlayerInstanceCheck() {
        Player* player = new Player(0, 0, 65, 33);
        TS_ASSERT_EQUALS(player->x, 0);
        TS_ASSERT_EQUALS(player->y, 0);
        
        TS_ASSERT(player->isGrounded);
        TS_ASSERT(player->lookRight);
    }

    void testEnemyInstanceCheck() {
        Enemy* enemy = new Enemy(0, 0, 0, 0, 65, 33);
        TS_ASSERT_EQUALS(enemy->x, 0);
        TS_ASSERT_EQUALS(enemy->y, 0);
        TS_ASSERT_EQUALS(enemy->pX, 0);
        TS_ASSERT_EQUALS(enemy->pY, 0);
    }

    void testCollectableInstanceCheck() {
        Collectable* coll = new Collectable(0, 0, 65, 33);
        TS_ASSERT_EQUALS(coll->x, 0);
        TS_ASSERT_EQUALS(coll->y, 0);
    }
};