#include <format>
#include <iostream>

#include "CommandContext.h"
#include "NextCommand.h"

const std::string NextCommand::NAME = "next";

NextCommand::NextCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void NextCommand::execute(const std::vector<std::string> & /*params*/) {
  auto &player = context->cur_player;
  auto &player_idx = context->cur_player_idx;
  auto &players = context->players;

  if (!player->hasRolled()) {
    std::cout << "You cannot end your turn without rolling!\n";
    return;
  }

  if (auto debt = player->getDebt() > 0) {
    // Player has existing debt,
    std::cout << std::format(
        "{} still owes ${}! You cannot end your turn until paying off "
        "your existing debts or declaring bankrupcy.\n",
        player->getName(), debt);
    return;
  }

  if (auto turns = player->getTurnsInTims()) {
    player->setTurnsInTims(turns + 1);
  }

  player->setRolled(false);
  player->setDoublesRolled(0);
  player->setCanRollAgain(false);

  // Transfer control to next active player
  auto num_players = static_cast<int>(players.size());
  do {
    player_idx = (player_idx + 1 < num_players) ? player_idx + 1 : 0;
    player = players[player_idx];
  } while (!player->isActive());

  context->board->displayBoard();

  std::cout << std::format("\n{}'s turn:\n--------------\n", player->getName());
}
