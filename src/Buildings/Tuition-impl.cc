module Tuition;

import <iostream>;
import <limits>;
import AcademicBuilding;
import OwnableBuilding;
import Player;


Tuition::Tuition()
    : UnownableBuilding{"TUITION"}, TUITION_AMOUNT{300}, PERCENT_AMOUNT{0.1} {}

void Tuition::processEvent(const std::shared_ptr<Player> player) {
  // Calculate net worth
  int fee = player->getBalance();
  for (auto &building : player->getProperties()) {
    fee += building.second->getCost();
    if (auto academic_building =
            std::dynamic_pointer_cast<AcademicBuilding>(building.second)) {
      fee += academic_building->getNumImprovements() *
             academic_building->getImprovementCost();
    }
  }
  fee *= PERCENT_AMOUNT;

  std::cout << "You must pay your tuition. Select one of the following payment "
               "options:\n";
  std::cout << "1. Pay $" << TUITION_AMOUNT << "\n";
  std::cout << "2. Pay " << PERCENT_AMOUNT * 100
            << "\% of your total net worth ($" << fee << ")\n";
  std::cout << "\n> ";

  int choice = 0;
  while (!(std::cin >> choice) || choice < 1 || choice > 2) {
    std::cout << "Invalid input. Try again: ", std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  fee = choice == 1 ? TUITION_AMOUNT : fee;

  auto reduced_funds = player->reduceFunds(fee);
  if (reduced_funds < fee) {
    // Player lacks sufficient funds
    player->setDebt(fee - reduced_funds);
    std::cout << "You lack sufficient funds. You owe $" << fee - reduced_funds
              << "\n";
  }
  player->displayBalance();
}
