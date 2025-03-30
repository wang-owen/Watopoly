#ifndef GOTOTIMS_H
#define GOTOTIMS_H

#include "UnownableBuilding.h"

class GoToTims : public UnownableBuilding {
public:
  GoToTims() : UnownableBuilding{"GO TO TIMS"} {}
  
  void processEvent(const std::shared_ptr<Player> &player) {}
};

#endif
