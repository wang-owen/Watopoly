#include <format>
#include <iostream>
#include <random>
#include <vector>

#include "../Dice.h"
#include "../Player.h"
#include "SLC.h"

SLC::SLC(const std::vector<std::shared_ptr<Building>> &buildings)
    : UnownableBuilding{"SLC"}, buildings{buildings} {}

void SLC::processEvent(const std::shared_ptr<Player> &player) {
  std::vector<double> probabilities = {1.0 / 8, 1.0 / 6, 1.0 / 6,  1.0 / 8,
                                       1.0 / 6, 1.0 / 6, 1.0 / 24, 1.0 / 24};

  switch (Dice::getDiscreteProbability(probabilities)) {
  case 0:
    // Back 3
    movePlayer(-3, player);
    break;
  case 1:
    // Back 2
    movePlayer(-2, player);
    break;
  case 2:
    // Back 1
    movePlayer(-1, player);
    break;
  case 3:
    // Forward 1
    movePlayer(1, player);
    break;
  case 4:
    // Forward 2
    movePlayer(2, player);
    break;
  case 5:
    // Forward 3
    movePlayer(3, player);
    break;
  case 6:
    // Go to DC Tims Line
    moveToIdx(10, player);
    break;
  case 7:
    // Advance to Collect OSAP
    moveToIdx(0, player);
    break;
  default:
    throw("Invalid random number");
  }
}

void SLC::movePlayer(int steps, const std::shared_ptr<Player> &player) {
  auto buildings_size = static_cast<int>(buildings.size());

  int cur_pos = player->getPosition();
  int new_pos;
  if (steps >= 0) {
    new_pos = (cur_pos + steps < buildings_size)
                  ? cur_pos + steps
                  : cur_pos + steps - buildings_size;
  } else {
    new_pos = (cur_pos + steps > 0) ? cur_pos + steps
                                    : buildings_size + cur_pos + steps;
  }

  player->setPosition(new_pos);
  buildings[cur_pos]->removePlayer(player);
  buildings[new_pos]->addPlayer(player);
  player->toggleRolled();

  std::cout << std::format("Moved {} steps to {}\n", steps,
                           buildings[new_pos]->getName());

  // Take action on building landed upon
  auto &building = buildings[new_pos];
  building->processEvent(player);
}

void SLC::moveToIdx(int i, const std::shared_ptr<Player> &player) {
  int cur_pos = player->getPosition();
  player->setPosition(i);
  buildings[cur_pos]->removePlayer(player);
  buildings[i]->addPlayer(player);
  player->toggleRolled();

  std::cout << std::format("Moved to {}\n", buildings[i]->getName());

  // Take action on building landed upon
  auto &building = buildings[i];
  building->processEvent(player);
}
