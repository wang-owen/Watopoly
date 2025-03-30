#ifndef GOOSENESTING_H
#define GOOSENESTING_H

#include "UnownableBuilding.h"

class GooseNesting : public UnownableBuilding {
public:
  GooseNesting() : UnownableBuilding{"GOOSE NESTING"} {}
  
  void processEvent(const std::shared_ptr<Player> &player) {}
};

#endif
