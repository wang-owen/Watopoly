#ifndef COOPFEE_H
#define COOPFEE_H

#include "UnownableBuilding.h"

class CoopFee : public UnownableBuilding {
public:
  CoopFee() : UnownableBuilding("COOP FEE"), FEE_AMOUNT{150} {}

  void processEvent(const std::shared_ptr<Player> player) {
    std::cout << "Immediately pay the Coop fee of $" << FEE_AMOUNT << ".\n";
    player->reduceFunds(FEE_AMOUNT);
  }

private:
  const int FEE_AMOUNT;
};

#endif
