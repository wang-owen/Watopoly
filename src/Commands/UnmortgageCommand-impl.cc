#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/OwnableBuilding.h"
#include "CommandContext.h"
#include "UnmortgageCommand.h"

const std::string UnmortgageCommand::NAME = "mortgage";

UnmortgageCommand::UnmortgageCommand(std::shared_ptr<CommandContext> context)
    : Command{context}, UNMORTGAGE_PERCENT{0.6} {}

void UnmortgageCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 1) {
    std::cout << "Usage: mortgage <property>\n";
    return;
  }

  auto &player = context->cur_player;
  if (!player->getProperties().count(params[0])) {
    std::cout << std::format("You do not own {}!\n", params[0]);
    return;
  }

  auto &property = player->getProperties().at(params[0]);
  if (property->isMortgaged()) {
    std::cout << std::format("{} is not mortgaged!\n", property->getName());
    return;
  }

  auto amt = property->getCost() * UNMORTGAGE_PERCENT;
  while (true) {
    std::cout << std::format("Do you want to mortgage {} for ${}? (y/n)",
                             property->getName(), amt);

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
      property->toggleMortgaged();
      player->reduceFunds(amt);
      std::cout << std::format("You have unmortgaged {} for ${}.\n",
                               property->getName(), amt);
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