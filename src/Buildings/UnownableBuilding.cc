#ifndef UNOWNABLEBUILDING_H
#define UNOWNABLEBUILDING_H

#include "Building.h"

class UnownableBuilding : public Building {
public:
  UnownableBuilding(const std::string &name) : Building{name} {}
};

#endif
