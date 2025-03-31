#include <iostream>
#include <sstream>

#include "../Buildings/AcademicBuilding.h"
#include "../Buildings/OwnableBuilding.h"
#include "CommandContext.h"
#include "MortgageCommand.h"

const std::string MortgageCommand::NAME = "mortgage";

MortgageCommand::MortgageCommand(std::shared_ptr<CommandContext> context)
    : Command{context}, MORTGAGE_PERCENT{0.5} {}

void MortgageCommand::execute(const std::vector<std::string> &params) {
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
  if (property->isMortgaged()) {
    std::cout << property->getName() << " is already mortgaged!\n";
    return;
  }

  if (auto academic_building =
          std::dynamic_pointer_cast<AcademicBuilding>(property)) {
    if (academic_building->getNumImprovements() > 0) {
      std::cout << "You must sell all improvements before mortgaging an "
                   "academic building!\n";
      return;
    }
  }

  auto amt = property->getCost() * MORTGAGE_PERCENT;
  while (true) {
    std::cout << "Do you want to mortgage " << property->getName() << " for $"
              << amt << "? (y/n)";

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
      player->increaseFunds(amt);
      std::cout << "You have mortgaged " << property->getName() << " for $"
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
