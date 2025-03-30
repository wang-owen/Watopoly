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

void RollCommand::execute(const std::vector<std::string> &params) {
  if (auto ctx = context.lock()) {
    auto &player = ctx->cur_player;
    if (player->hasRolled()) {
      std::cout << "You have already rolled this turn!\n";
      return;
    }
    std::cout << "PlayerRolled? " << player->hasRolled() << "\n";
    // generates player movement steps
    int steps;
    int die1, die2;
    if (ctx->testing) {
      if (params.size() < 2) {
        std::cout << "Did not specify two dice rolls, rolling randomly.\n";
        auto rolls = Dice::roll(6, 2);
        die1 = rolls[0];
        die2 = rolls[1];
        steps = die1 + die2;
      } else if (!(std::stoi(params[0]) && std::stoi(params[1]))) {
        std::cout << "Did not specify two dice rolls, rolling randomly.\n";
        auto rolls = Dice::roll(6, 2);
        die1 = rolls[0];
        die2 = rolls[1];
        steps = die1 + die2;
      } else {
        die1 = std::stoi(params[0]);
        die2 = std::stoi(params[1]);
        steps = die1 + die2;
      }
    } else {
      auto rolls = Dice::roll(6, 2);
      die1 = rolls[0];
      die2 = rolls[1];
      steps = die1 + die2;
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

    player->move(steps, ctx->board->getBuildings());
    player->toggleRolled();
    std::cout << "PlayerRolled? " << player->hasRolled() << "\n";
    return;
  }
  throw("Failed to acquire player pointer");
}
