#include <iostream>
#include <random>
#include <vector>

#include "../Dice.h"
#include "../Player.h"
#include "SLC.h"

SLC::SLC(const std::vector<std::shared_ptr<Building>> &buildings)
    : UnownableBuilding{"SLC"}, buildings{buildings} {}

void SLC::processEvent(const std::shared_ptr<Player> player) {
  std::vector<double> probabilities = {1.0 / 8, 1.0 / 6, 1.0 / 6,  1.0 / 8,
                                       1.0 / 6, 1.0 / 6, 1.0 / 24, 1.0 / 24};

  switch (Dice::getDiscreteProbability(probabilities)) {
  case 0:
    // Back 3
    player->move(-3, buildings);
    break;
  case 1:
    // Back 2
    player->move(-2, buildings);
    break;
  case 2:
    // Back 1
    player->move(-1, buildings);
    break;
  case 3:
    // Forward 1
    player->move(1, buildings);
    break;
  case 4:
    // Forward 2
    player->move(2, buildings);
    break;
  case 5:
    // Forward 3
    player->move(3, buildings);
    break;
  case 6:
    // Go to DC Tims Line
    player->moveToIdx(10, buildings);
    break;
  case 7:
    // Advance to Collect OSAP
    player->moveToIdx(0, buildings);
    break;
  default:
    throw("Invalid random number");
  }
}
