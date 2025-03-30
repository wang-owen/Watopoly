#include <format>
#include <iostream>

#include "../Player.h"
#include "DCTimsLine.h"

DCTimsLine::DCTimsLine() : UnownableBuilding("DC TIMS LINE"), FEE_AMOUNT{50} {}

void DCTimsLine::processEvent(const std::shared_ptr<Player> &player) {
  int turns_in_tims = player->getTurnsInTims();
  if (turns_in_tims == 0) {
    return;
  }

  if (turns_in_tims < 3) {
    std::cout << std::format("You are stuck in the DC Tims Line! Pay ${} or "
                             "use a Roll Up the Rim cup to get out.\n",
                             FEE_AMOUNT);
  } else {
    std::cout << std::format("You have been in the DC Tims Line for three "
                             "turns! You must pay ${} or "
                             "use a Roll Up the Rim cup to get out.\n",
                             FEE_AMOUNT);
  }

  bool error = true;
  while (error) {
    std::cout << "Would you like to pay the fee or use a cup?\n";
    std::cout << std::format("1. Pay ${}\n", FEE_AMOUNT);
    std::cout << std::format("2. Use a Roll Up the Rim cup ({} remaining)\n",
                             player->getCups());
    if (turns_in_tims < 3) {
      std::cout << "3. Do nothing\n";
    }
    std::cout << "\n> ";

    int choice = 0;
    while (!(std::cin >> choice) ||
           (turns_in_tims < 3 && (choice < 1 || choice > 3)) || choice != 1 ||
           choice != 2) {
      std::cout << "Invalid input. Try again: ", std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1: {
      if (turns_in_tims < 3 && player->getBalance() < FEE_AMOUNT) {
        std::cout << "You lack sufficient funds.\n";
        continue;
      }
      auto reduced_funds = player->reduceFunds(FEE_AMOUNT);
      if (reduced_funds < FEE_AMOUNT) {
        // Player lacks sufficient funds
        player->setDebt(FEE_AMOUNT - reduced_funds);
        std::cout << std::format("You lack sufficient funds. You owe ${}\n",
                                 FEE_AMOUNT - reduced_funds);
      }
      std::cout << std::format("New balance: ${}\n", player->getBalance());
      error = false;
      break;
    }

    case 2: {
      if (player->getCups() == 0) {
        std::cout << "You do not have any Roll up the Rim cups!\n";
        continue;
      }
      player->removeCup();
      player->setTurnsInTims(0);
      std::cout << "You have left the DC Tims Line.\n";
      break;
    }
    case 3: {
      error = false;
      break;
    }
    }
  }
}