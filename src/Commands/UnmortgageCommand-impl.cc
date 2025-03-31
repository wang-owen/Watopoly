#include <iostream>
#include <sstream>

#include "../Buildings/OwnableBuilding.h"
#include "CommandContext.h"
#include "UnmortgageCommand.h"

const std::string UnmortgageCommand::NAME = "unmortgage";

UnmortgageCommand::UnmortgageCommand(std::shared_ptr<CommandContext> context)
    : Command{context}, UNMORTGAGE_PERCENT{0.6} {}

void UnmortgageCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 1) {
    std::cout << "Usage: mortgage <property>\n";
    return;
  }

  auto &player = context->cur_player;
  if (!player->getProperties().count(params[0])) {
    std::cout << "You do not own " << params[0] << "!\n";
    return;
  }

  auto &property = player->getProperties().at(params[0]);
  if (!(property->isMortgaged())) {
    std::cout << property->getName() << " is not mortgaged!\n";
    return;
  }

  auto amt = property->getCost() * UNMORTGAGE_PERCENT;
  while (true) {
    std::cout << "Do you want to mortgage " << property->getName() << " for $"
              << amt << "? (y/n) ";

    std::string input, extra;
    char answer;
    std::getline(std::cin, input);
    std::istringstream iss{input};

    if (!(iss >> answer) || (iss >> extra)) {
      std::cout << "Invalid input. Try again.\n";
      continue;
    }

    switch (std::tolower(answer)) {
    case 'y': {
      if (player->getBalance() < amt) {
        std::cout << "You lack sufficient funds.\n";
        return;
      }
      property->toggleMortgaged();
      player->reduceFunds(amt);
      std::cout << "You have unmortgaged " << property->getName() << " for $"
                << amt << ".\n";
      return;
    }
    case 'n': {
      return;
    }
    default:
      continue;
    }
  }
}
