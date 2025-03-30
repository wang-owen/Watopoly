#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H

#include <format>
#include <iostream>

#include "UnownableBuilding.h"

class CollectOSAP : public UnownableBuilding {
public:
  CollectOSAP() : UnownableBuilding{"COLLECT OSAP"}, OSAP_AMOUNT{200} {}

  void processEvent(const std::shared_ptr<Player> &player) override {
    std::cout << "You have collected your OSAP grant of $200\n";
    player->increaseFunds(OSAP_AMOUNT);
    std::cout << std::format("New balance: ${}\n", player->getBalance());
  }

private:
  const int OSAP_AMOUNT;
};

#endif
