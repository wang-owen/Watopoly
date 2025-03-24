#ifndef OWNABLEBUILDING_H
#define OWNABLEBUILDING_H

#include "Building.h"

class OwnableBuilding : public Building {
public:
  OwnableBuilding() : Building{} {}

  virtual int getPurchaseCost() const = 0;

  virtual int getFee() const = 0;
};

#endif
