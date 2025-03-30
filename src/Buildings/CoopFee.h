#ifndef COOPFEE_H
#define COOPFEE_H

#include "UnownableBuilding.h"

class CoopFee : public UnownableBuilding {
public:
  CoopFee() : UnownableBuilding{"COOP FEE"} {}
  
  void processEvent(const std::shared_ptr<Player> &player) {}
};

#endif
