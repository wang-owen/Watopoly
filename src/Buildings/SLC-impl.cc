#include <format>
#include <iostream>
#include <random>
#include <vector>

#include "../CommandCenter.h"
#include "../Dice.h"
#include "SLC.h"

SLC::SLC(const std::vector<std::shared_ptr<Building>> &buildings)
    : UnownableBuilding{"SLC"}, buildings{buildings} {}

void SLC::processEvent(const std::shared_ptr<Player> &player) {
  std::vector<double> probabilities = {1.0 / 8, 1.0 / 6, 1.0 / 6,  1.0 / 8,
                                       1.0 / 6, 1.0 / 6, 1.0 / 24, 1.0 / 24};

  switch (Dice::getDiscreteProbability(probabilities)) {
  case 0:
    // Back 3
    CommandCenter::movePlayer(-3, player, buildings);
    break;
  case 1:
    // Back 2
    CommandCenter::movePlayer(-2, player, buildings);
    break;
  case 2:
    // Back 1
    CommandCenter::movePlayer(-1, player, buildings);
    break;
  case 3:
    // Forward 1
    CommandCenter::movePlayer(1, player, buildings);
    break;
  case 4:
    // Forward 2
    CommandCenter::movePlayer(2, player, buildings);
    break;
  case 5:
    // Forward 3
    CommandCenter::movePlayer(3, player, buildings);
    break;
  case 6:
    // Go to DC Tims Line
    CommandCenter::movePlayerToIdx(10, player, buildings);
    break;
  case 7:
    // Advance to Collect OSAP
    CommandCenter::movePlayerToIdx(0, player, buildings);
    break;
  default:
    throw("Invalid random number");
  }
}
