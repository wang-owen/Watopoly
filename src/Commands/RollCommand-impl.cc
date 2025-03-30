#include <format>
#include <iostream>

#include "../Buildings/Building.h"
#include "../Buildings/OwnableBuilding.h"
#include "../Buildings/UnownableBuilding.h"
#include "../Dice.h"
#include "CommandContext.h"
#include "RollCommand.h"

const std::string RollCommand::NAME = "roll";

RollCommand::RollCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

void RollCommand::execute(const std::vector<std::string> & /*params*/) {
  if (auto ctx = context.lock()) {
    auto &player = ctx->cur_player;
    if (player->hasRolled()) {
      std::cout << "You have already rolled this turn!\n";
      return;
    }

    // Generate dice roll
    auto rolls = Dice::roll(6, 2);
    int steps = rolls[0] + rolls[1];

    // Player is stuck in DC Tims Line
    if (player->getTurnsInTims()) {
      if (rolls[0] == rolls[1]) {
        std::cout << "You rolled doubles! You have left the DC Tims Line.\n";
        player->setTurnsInTims(0);
      } else {
        std::cout
            << "You failed to roll doubles, you remain in the DC Tims Line.\n";
      }
      return;
    }

    player->move(steps, ctx->board->getBuildings());
    player->toggleRolled();
    return;
  }
  throw("Failed to acquire player pointer");
}
