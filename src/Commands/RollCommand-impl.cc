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

RollCommand::RollCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void RollCommand::execute(const std::vector<std::string> &params) {
  auto &player = context->cur_player;
  if (player->hasRolled()) {
    std::cout << "You have already rolled this turn!\n";
    return;
  }

  // Generate dice roll
  auto rolls = Dice::roll(6, 2);
  int die1 = rolls[0];
  int die2 = rolls[1];

  if (context->testing) {
    if (params.size() == 2) {
      std::istringstream iss{params[0]};
      if (!(iss >> die1)) {
        std::cout << "Usage: roll [die1] [die2]\n";
        return;
      }
      iss = std::istringstream{params[1]};
      if (!(iss >> die2)) {
        std::cout << "Usage: roll [die1] [die2]\n";
        return;
      }
    } else if (params.size() != 0) {
      std::cout << "Usage: roll [die1] [die2]\n";
    }
  }

  // Player is stuck in DC Tims Line
  if (player->getTurnsInTims()) {
    if (die1 == die2) {
      std::cout << "You rolled doubles! You have left the DC Tims Line.\n";
      player->setTurnsInTims(0);
    } else {
      std::cout
          << "You failed to roll doubles, you remain in the DC Tims Line.\n";
    }
    return;
  }

  player->move(die1 + die2, context->board->getBuildings());
  player->toggleRolled();
  context->board->displayBoard();
}
