#include <format>
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
    std::cout << std::format("You do not own {}!\n", params[0]);
    return;
  }

  auto &property = player->getProperties().at(params[0]);
  if (property->isMortgaged()) {
    std::cout << std::format("{} is already mortgaged!\n", property->getName());
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
      player->increaseFunds(amt);
      std::cout << std::format("You have mortgaged {} for ${}.\n",
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
