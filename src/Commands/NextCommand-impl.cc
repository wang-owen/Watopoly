#include <format>
#include <iostream>

#include "CommandContext.h"
#include "NextCommand.h"

const std::string NextCommand::NAME = "next";

NextCommand::NextCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool NextCommand::execute() {
  if (auto ctx = context.lock()) {
    auto num_players = static_cast<int>(ctx->players.size());
    ctx->cur_player_idx =
        (ctx->cur_player_idx + 1 < num_players) ? ctx->cur_player_idx + 1 : 0;
    ctx->cur_player = ctx->players[ctx->cur_player_idx];

    std::cout << std::format("\nPlayer {} turn:\n--------------",
                             ctx->cur_player_idx + 1);

    return true;
  }
  return false;
}