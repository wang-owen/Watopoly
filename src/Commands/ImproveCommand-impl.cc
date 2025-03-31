#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/AcademicBuilding.h"
#include "CommandContext.h"
#include "ImproveCommand.h"

const std::string ImproveCommand::NAME = "improve";

ImproveCommand::ImproveCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void ImproveCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 2 || (params[1] != "buy" && params[1] != "sell")) {
    std::cout << "Usage: improve <property> buy/sell\n";
    return;
  }

  auto &player = context->cur_player;
  if (!player->getProperties().count(params[0])) {
    std::cout << std::format("You do not own {}!\n", params[0]);
    return;
  }

  if (auto building = std::dynamic_pointer_cast<AcademicBuilding>(
          player->getProperties().at(params[0]))) {
    auto name = building->getName();
    if (params[1] == "buy") {
      // Buy
      if (building->getNumImprovements() >=
          AcademicBuilding::MAX_IMPROVEMENTS) {
        std::cout << std::format(
            "{} already has the maximum number of improvements!\n", name);
        return;
      }

      auto cost = building->getImprovementCost();
      std::cout << std::format("Improvement cost: ${}. Purchase? (y/n)", cost);
      while (true) {
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
          if (player->getBalance() < cost) {
            std::cout << "Insufficient funds.\n";
            return;
          }
          player->reduceFunds(cost);
          building->improve();
          
          context->board->displayBoard();
          std::cout << std::format("{} has been improved!\n", name);
          std::cout << std::format("New tuition cost: ${}\n",
                                   building->getFee());
          return;
        }
        case 'n': {
          return;
        }
        default:
          continue;
        }
      }
    } else {
      // Sell
      if (building->getNumImprovements() == 0) {
        std::cout << std::format("{} already has no improvements!\n", name);
        return;
      }

      auto cost = building->getImprovementCost() / 2;
      std::cout << std::format("Improvement cost: ${}. Sell? (y/n)", cost);
      while (true) {
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
          player->increaseFunds(cost);
          building->impair();
          
          context->board->displayBoard();
          std::cout << std::format("{} has lost an improvement.\n", name);
          std::cout << std::format("New tuition cost: ${}\n",
                                   building->getFee());
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
  } else {
    std::cout << "You can only improve academic buildings.\n";
  }
}
