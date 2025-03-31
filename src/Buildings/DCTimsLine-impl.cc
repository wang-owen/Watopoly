#include <iostream>
#include <limits>

#include "../Player.h"
#include "DCTimsLine.h"

DCTimsLine::DCTimsLine() : UnownableBuilding("DC TIMS LINE"), FEE_AMOUNT{50} {}

void DCTimsLine::processEvent(const std::shared_ptr<Player> player) {
  int turns_in_tims = player->getTurnsInTims();
  if (turns_in_tims == 0) {
    return;
  }

  if (turns_in_tims < 3) {
    std::cout << "You are stuck in the DC Tims Line! Pay $" << FEE_AMOUNT
              << " or use a Roll Up the Rim cup to get out.\n ";
  } else {
    std::cout << "You have been in the DC Tims Line for three "
                 "turns! You must pay $"
              << FEE_AMOUNT << " or use a Roll Up the Rim cup to get out.\n";
  }

  bool error = true;
  while (error) {
    std::cout << "Would you like to pay the fee or use a cup?\n";
    std::cout << "1. Pay $" << FEE_AMOUNT << "\n";
    std::cout << "2. Use a Roll Up the Rim cup (" << player->getCups()
              << " remaining)\n";
    if (turns_in_tims < 3) {
      std::cout << "3. Do nothing\n";
    }
    std::cout << "\n> ";

    int choice = 0;
    while (!(std::cin >> choice) || choice < 1 ||
           (turns_in_tims < 3 && choice > 3) ||
           (turns_in_tims >= 3 && choice > 2)) {
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
        std::cout << "You lack sufficient funds. You owe $"
                  << FEE_AMOUNT - reduced_funds << "\n";
      } else {
        std::cout << "You have left the DC Tims Line.\n";
      }
      player->setTurnsInTims(0);
      player->displayBalance();
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
      error = false;
      break;
    }
    case 3: {
      error = false;
      break;
    }
    }
  }
}
