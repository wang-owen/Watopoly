#include <format>
#include <iostream>

#include "../Player.h"
#include "CoopFee.h"

CoopFee::CoopFee() : UnownableBuilding("COOP FEE") {}

void CoopFee::processEvent(const std::shared_ptr<Player> &player) {
  std::cout << std::format("Immediately pay ${} to the School.\n", FEE_AMOUNT);
  player->reduceFunds(FEE_AMOUNT);
}
