#include <format>
#include <iostream>

#include "../Buildings/OwnableBuilding.h"
#include "BankruptCommand.h"
#include "CommandContext.h"

const std::string BankruptCommand::NAME = "bankrupt";

BankruptCommand::BankruptCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void BankruptCommand::execute(const std::vector<std::string> & /*params*/) {
  auto &player = context->cur_player;

  if (player->getDebt() == 0) {
    std::cout << "You cannot declare bankruptcy with zero debt!\n";
    return;
  }

  auto &building = context->board->getBuildings()[player->getPosition()];
  if (auto b = std::dynamic_pointer_cast<OwnableBuilding>(building)) {
    // Player's assets go to building owner
    auto owner = b->getOwner();
    for (auto &[_, property] : player->getProperties()) {
      property->setOwner(owner);
      owner->addProperty(property);
    }
    // Transfer Roll Up the Rim tickets to owner
    for (int n = 0; n < player->getCups(); n++) {
      owner->addCup();
    }
  } else {
    // Player's assets go to bank
    for (auto &[_, property] : player->getProperties()) {
      property->auctionProperty(player, context->players);
    }
  }

  player->deactivate();

  // Transfer control to next active player
  auto num_players = static_cast<int>(context->players.size());
  do {
    context->cur_player_idx = (context->cur_player_idx + 1 < num_players)
                                  ? context->cur_player_idx + 1
                                  : 0;
    player = context->players[context->cur_player_idx];
  } while (!player->isActive());

  context->board->displayBoard();

  std::cout << std::format("\nPlayer {} turn:\n--------------\n",
                           context->cur_player_idx + 1);
}
