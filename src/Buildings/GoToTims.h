#ifndef GOTOTIMS_H
#define GOTOTIMS_H

#include <iostream>

#include "../Player.h"
#include "UnownableBuilding.h"

class GoToTims : public UnownableBuilding {
public:
  GoToTims(const std::vector<std::shared_ptr<Building>> &buildings)
      : UnownableBuilding{"GO TO TIMS"}, buildings{buildings} {}

  void processEvent(const std::shared_ptr<Player> &player) override {
    std::cout << "You have been sent directly to DC Tims Line.\n";
    player->setTurnsInTims(1);
    player->moveToIdx(10, buildings);
  }

private:
  const std::vector<std::shared_ptr<Building>> &buildings;
};

#endif
