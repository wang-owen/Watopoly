#ifndef COOPFEE_H
#define COOPFEE_H

#include "UnownableBuilding.h"

class CoopFee : public UnownableBuilding {
public:
  CoopFee();

  void processEvent(const std::shared_ptr<Player> &player);

private:
  static const int FEE_AMOUNT = 150;
};

#endif
