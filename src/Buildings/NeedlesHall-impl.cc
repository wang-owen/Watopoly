#include <iostream>

#include "../Dice.h"
#include "../Player.h"
#include "NeedlesHall.h"

NeedlesHall::NeedlesHall() : UnownableBuilding{"NeedlesHall"} {}

void NeedlesHall::processEvent(const std::shared_ptr<Player> player) {
  std::vector<double> probabilities = {1.0 / 18, 1.0 / 9, 1.0 / 6, 1.0 / 3,
                                       1.0 / 6,  1.0 / 9, 1.0 / 18};

  switch (Dice::getDiscreteProbability(probabilities)) {
  case 0:
    player->reduceFunds(200);
    std::cout << "You have lost $200...\n";
    break;
  case 1:
    player->reduceFunds(100);
    std::cout << "You have lost $100...\n";
    break;
  case 2:
    player->reduceFunds(50);
    std::cout << "You have lost $50...\n";
    break;
  case 3:
    player->increaseFunds(25);
    std::cout << "You have won $25!\n";
    break;
  case 4:
    player->increaseFunds(50);
    std::cout << "You have won $50!\n";
    break;
  case 5:
    player->increaseFunds(100);
    std::cout << "You have won $100!\n";
    break;
  case 6:
    player->increaseFunds(200);
    std::cout << "You have won $200!\n";
    break;
  default:
    throw("Invalid random number");
  }
  player->displayBalance();
}