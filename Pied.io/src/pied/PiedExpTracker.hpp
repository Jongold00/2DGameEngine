#ifndef PIED_EXP_TRACKER_HPP
#define PIED_EXP_TRACKER_HPP

#include "base/SDLGraphicsProgram.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "PiedPlayer.hpp"
#include <cmath>


class PiedPlayer;

class PiedExpTracker: public GenericComponent {
public:

  PiedExpTracker(GameObject & gameObject, PiedPlayer & playerScript);
  
  virtual void update(Level & level) override;

  int getUnspentPoints();

  void addExp(int delta);

  void spendPointHealth();
  void spendPointSpeed();
  void spendPointBulletSize();
  void spendPointFireRate();
  

private:

    int CalculateCurrentLevel();

    void LevelUp();

    PiedPlayer & playerScript;

    int currentLevel = 1;
    int spentPoints = 0;
    int totalExp = 0;




};


#endif