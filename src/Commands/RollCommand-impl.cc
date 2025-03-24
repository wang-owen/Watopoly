#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/Building.h"
#include "../Buildings/OwnableBuilding.h"
#include "../Dice.h"
#include "CommandContext.h"
#include "RollCommand.h"

const std::string RollCommand::NAME = "roll";

RollCommand::RollCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool RollCommand::execute() {
  if (auto ctx = context.lock()) {
    // Generate dice roll
    Dice dice{6};
    int steps = 0;
    for (auto n : dice.roll(2)) {
      steps += n;
    }
    auto &buildings = ctx->board->getBuildings();
    auto &player = ctx->cur_player;
    auto buildings_size = static_cast<int>(buildings.size());

    int cur_pos = player->getPosition();
    int new_pos = (cur_pos + steps < buildings_size)
                      ? cur_pos + steps
                      : cur_pos + steps - buildings_size;

    player->setPosition(new_pos);
    buildings[cur_pos]->removePiece(player->getPiece());
    buildings[new_pos]->addPiece(player->getPiece());

    std::cout << std::format("Moved {} steps to {}\n", steps,
                             buildings[new_pos]->getName());

    // Check if building is purchaseable
    auto &building = buildings[new_pos];
    if (auto property = std::dynamic_pointer_cast<OwnableBuilding>(building)) {
      if (!property->hasOwner()) {
        // Building is available for purchase
        auto property_cost = property->getCost();
        while (true) {
          std::cout << std::format("\nCurrent balance: ${}\n",
                                   player->getBalance());
          std::cout << std::format(
              "Would you like to purchase {} for ${}? (y/n) ",
              property->getName(), property_cost);

          std::string input, extra;
          char answer;
          std::getline(std::cin, input);
          std::istringstream iss{input};

          if (!(iss >> answer) || (iss >> extra)) {
            std::cout << "Invalid input. Try again.\n";
            continue;
          }

          switch (std::tolower(answer)) {
          case 'y':
            // Attempt to purchase property
            // Check player balance
            if (player->getBalance() < property_cost) {
              std::cout << "Insufficient funds.\n";
            } else {
              player->reduceFunds(property_cost);
              property->setOwner(player);
              player->addProperty(property);
            }

            std::cout << std::format("\n{} has purchased {} for ${}\n",
                                     player->getName(), property->getName(),
                                     property_cost);
            std::cout << std::format("New balance: ${}\n",
                                     player->getBalance());
            return true;

          case 'n':
            return true;

          default:
            // Loop
            continue;
          }
        }
      }
    }
    return true;
  }
  return false;
}