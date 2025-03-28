#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/Building.h"
#include "../Buildings/OwnableBuilding.h"
#include "../Buildings/UnownableBuilding.h"
#include "../Dice.h"
#include "CommandContext.h"
#include "RollCommand.h"

const std::string RollCommand::NAME = "roll";

RollCommand::RollCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool RollCommand::execute(std::vector<std::string> params) {
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

    // Take action on building landed upon
    auto &building = buildings[new_pos];
    if (auto property = std::dynamic_pointer_cast<OwnableBuilding>(building)) {
      ownableBuildingAction(player, property);
    } else if (auto b =
                   std::dynamic_pointer_cast<UnownableBuilding>(building)) {
      // TODO: Unownable building action
    }
    return true;
  }
  throw("Failed to acquire player pointer");
  return false;
}

bool RollCommand::ownableBuildingAction(
    std::shared_ptr<Player> player, std::shared_ptr<OwnableBuilding> property) {
  auto property_name = property->getName();

  std::cout << std::format("\nCurrent balance: ${}\n", player->getBalance());

  if (!property->hasOwner()) {
    // Building is available for purchase
    auto property_cost = property->getCost();
    bool error = true;
    while (error) {
      std::cout << std::format("Would you like to purchase {} for ${}? (y/n) ",
                               property_name, property_cost);

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
                                 player->getName(), property_name,
                                 property_cost);
        error = false;
        break;

      case 'n':
        error = false;
        break;

      default:
        // Loop
        continue;
      }
    }
  } else {
    // Pay fee
    auto fee = property->getFee();
    std::cout << std::format("{} Fee: ${}\n", property_name, fee);
    auto reduced_funds = player->reduceFunds(fee);
    property->getOwner()->increaseFunds(reduced_funds);
    if (reduced_funds < fee) {
      // Player lacks sufficient funds
      player->setDebt(fee - reduced_funds);
      std::cout << std::format("You lack sufficient funds. You owe ${}\n",
                               fee - reduced_funds);
    }
  }
  std::cout << std::format("New balance: ${}\n", player->getBalance());
  return true;
}