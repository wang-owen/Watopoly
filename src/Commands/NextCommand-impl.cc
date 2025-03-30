#include <format>
#include <iostream>

#include "CommandContext.h"
#include "NextCommand.h"

const std::string NextCommand::NAME = "next";

NextCommand::NextCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

void NextCommand::execute(const std::vector<std::string> & /*params*/) {
  if (auto ctx = context.lock()) {
    auto &player = ctx->cur_player;
    auto &player_idx = ctx->cur_player_idx;
    auto &players = ctx->players;

    if (!player->hasRolled()) {
      std::cout << "You cannot end your turn without rolling!\n";
      return;
    }

    if (auto debt = player->getDebt() > 0) {
      // Player has existing debt,
      std::cout << std::format(
          "Player {} still owes ${}! You cannot end your turn until paying off "
          "your existing debts or declaring bankrupcy.\n",
          player_idx + 1, debt);
      return;
    }

    if (auto turns = player->getTurnsInTims()) {
      player->setTurnsInTims(turns + 1);
    }

    player->toggleRolled();

    // Transfer control to next active player
    auto num_players = static_cast<int>(players.size());
    do {
      player_idx = (player_idx + 1 < num_players) ? player_idx + 1 : 0;
      player = players[player_idx];
    } while (!player->isActive());

    std::cout << std::format("\nPlayer {} turn:\n--------------\n",
                             player_idx + 1);
    return;
  }
  throw("Failed to acquire player pointer");
}