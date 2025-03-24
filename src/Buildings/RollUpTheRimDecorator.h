#ifndef ROLLUPTHERIM_H
#define ROLLUPTHERIM_H

#include "UnownableBuilding.h"

class RollUpTheRimDecorator : public UnownableBuilding {
public:
  RollUpTheRimDecorator(std::shared_ptr<UnownableBuilding> building)
      : UnownableBuilding{building->getName()} {}
};

#endif
