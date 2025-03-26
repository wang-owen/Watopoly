#include <format>
#include <iostream>

#include "CommandContext.h"
#include "NextCommand.h"

const std::string NextCommand::NAME = "next";

NextCommand::NextCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool NextCommand::execute() {
  if (auto ctx = context.lock()) {
    auto &cur_player = ctx->cur_player;
    auto &cur_player_idx = ctx->cur_player_idx;
    auto &players = ctx->players;

    if (auto debt = cur_player->getDebt() > 0) {
      // Player has existing debt,
      std::cout << std::format(
          "Player {} still owes ${}! You cannot end your turn until paying off "
          "your existing debts or declaring bankrupcy.\n",
          cur_player_idx + 1, debt);
      return true;
    }

    auto num_players = static_cast<int>(players.size());
    cur_player_idx =
        (cur_player_idx + 1 < num_players) ? cur_player_idx + 1 : 0;
    cur_player = players[cur_player_idx];

    std::cout << std::format("\nPlayer {} turn:\n--------------",
                             cur_player_idx + 1);

    return true;
  }
  throw("Failed to acquire player pointer");
  return false;
}