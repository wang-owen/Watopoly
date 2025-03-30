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

    // player goes to DC Tims Line if they roll doubles three times in a row
    if (rolls[0] == rolls[1] && player->getNumDoubles() == 2) {
      std::cout << "You rolled doubles three times in a row! You are stuck in the DC Tims Line.\n";
      player->setNumDoubles(0);
      player->toggleRolled();
      player->setTurnsInTims(1);
      player->moveToIdx(10, ctx->board->getBuildings());
      return;
    } 

    player->move(steps, ctx->board->getBuildings());

    if (rolls[0] == rolls[1]) {
      std::cout << "You rolled doubles! You get to roll again.\n";
      player->setNumDoubles(player->getNumDoubles() + 1);
    } else {
      player->setNumDoubles(0);
      player->toggleRolled();
    }
    return;
  }
  throw("Failed to acquire player pointer");
}
