#include <format>
#include <iostream>

#include "../Player.h"
#include "Tuition.h"

Tuition::Tuition()
    : UnownableBuilding{"TUITION"}, TUITION_AMOUNT{300}, PERCENT_AMOUNT{10} {}

void Tuition::processEvent(const std::shared_ptr<Player> &player) {
  int fee = player->getBalance() * (PERCENT_AMOUNT / 100);

  std::cout << "You must pay your tuition. Select one of the following payment "
               "options:\n";
  std::cout << std::format("1. Pay ${}\n", TUITION_AMOUNT);
  std::cout << std::format("1. Pay {}\% of your total net worth (${})\n",
                           PERCENT_AMOUNT, static_cast<int>(fee));
  std::cout << "\n> ";

  int choice = 0;
  while (!(std::cin >> choice) || choice != 1 || choice != 2) {
    std::cout << "Invalid input. Try again: ", std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  int fee = choice == 1 ? TUITION_AMOUNT : fee;

  auto reduced_funds = player->reduceFunds(fee);
  if (reduced_funds < fee) {
    // Player lacks sufficient funds
    player->setDebt(fee - reduced_funds);
    std::cout << std::format("You lack sufficient funds. You owe ${}\n",
                             fee - reduced_funds);
  }
  std::cout << std::format("New balance: ${}\n", player->getBalance());
}