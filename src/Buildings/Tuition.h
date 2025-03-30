#ifndef TUITION_H
#define TUITION_H

#include "UnownableBuilding.h"

class Tuition : public UnownableBuilding {
public:
  Tuition() : UnownableBuilding{"TUITION"} {}

  void processEvent(const std::shared_ptr<Player> &player) override {}
};

#endif
