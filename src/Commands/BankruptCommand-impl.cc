#include <format>
#include <iostream>

#include "../Buildings/OwnableBuilding.h"
#include "BankruptCommand.h"
#include "CommandContext.h"

const std::string BankruptCommand::NAME = "bankrupt";

BankruptCommand::BankruptCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool BankruptCommand::execute(std::vector<std::string> params) {
  if (auto ctx = context.lock()) {
    auto &player = ctx->cur_player;

    if (player->getDebt() == 0) {
      std::cout << "You cannot declare bankruptcy with zero debt!\n";
      return true;
    }

    auto &players = ctx->players;
    auto &building = ctx->board->getBuildings()[player->getPosition()];
    if (auto b = std::dynamic_pointer_cast<OwnableBuilding>(building)) {
      // Player's assets go to building owner
      auto owner = b->getOwner();
      for (auto &[name, property] : player->getProperties()) {
        // TODO: Determine if 'improvements' transfer over
        property->setOwner(owner);
        owner->addProperty(property);
      }
      // TODO: Transfer Roll Up the Rim tickets to owner
    } else {
      // Player's assets go to bank
      for (auto &[name, property] : player->getProperties()) {
        property->setOwner(nullptr);
        // TODO: Auction properties to all players
      }

      // TODO: Destroy Roll Up the Rim tickets
    }

    player->deactivate();

    // TODO: Call 'next' command
  }
  throw("Failed to acquire player pointer");
  return false;
}