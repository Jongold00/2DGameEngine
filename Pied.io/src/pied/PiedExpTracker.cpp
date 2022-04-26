#include "PiedExpTracker.hpp"
#include "base/SoundManager.hpp"

PiedExpTracker::PiedExpTracker(GameObject & go, PiedPlayer & ps):
GenericComponent(go),
playerScript(ps)
{

}

void
PiedExpTracker::update(Level & level)
{
    if (currentLevel != CalculateCurrentLevel())
    {
        currentLevel = CalculateCurrentLevel();
    }
}

int
PiedExpTracker::CalculateCurrentLevel()
{
    int ret = 0;
    double expHolder = (double)totalExp;
        
    while (expHolder > 0)
    {
        ret++;
        expHolder -= (50 * pow(1.1, ret));
    }   
    return ret;
}


int
PiedExpTracker::getUnspentPoints()
{
    return currentLevel - spentPoints;
}

void
PiedExpTracker::addExp(int delta)
{
    totalExp += delta;
}

void
PiedExpTracker::spendPointHealth()
{
    if (getUnspentPoints() <= 0) return;
    playerScript.spendPointHealth();
    spentPoints++;
    SoundManager::getInstance().playSoundEffect(4);
}

void
PiedExpTracker::spendPointSpeed()
{
    if (getUnspentPoints() <= 0) return;
    playerScript.spendPointSpeed();
    spentPoints++;
    SoundManager::getInstance().playSoundEffect(4);

}

void
PiedExpTracker::spendPointBulletSize()
{
    if (getUnspentPoints() <= 0) return;
    playerScript.spendPointBulletSize();
    spentPoints++;
    SoundManager::getInstance().playSoundEffect(4);
}

void
PiedExpTracker::spendPointFireRate()
{
    if (getUnspentPoints() <= 0) return;
    playerScript.spendPointFireRate();
    spentPoints++;    
    SoundManager::getInstance().playSoundEffect(4);
}
