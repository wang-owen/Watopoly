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

bool RollCommand::execute() {
  if (auto ctx = context.lock()) {
    auto &player = ctx->cur_player;
    if (player->hasRolled()) {
      std::cout << "You have already rolled this turn!\n";
      return true;
    }

    // Generate dice roll
    int steps = 0;
    for (auto n : Dice::roll(6, 2)) {
      steps += n;
    }
    auto &buildings = ctx->board->getBuildings();
    auto buildings_size = static_cast<int>(buildings.size());

    int cur_pos = player->getPosition();
    int new_pos = (cur_pos + steps < buildings_size)
                      ? cur_pos + steps
                      : cur_pos + steps - buildings_size;

    player->setPosition(new_pos);
    buildings[cur_pos]->removePlayer(player);
    buildings[new_pos]->addPlayer(player);
    player->toggleRolled();

    std::cout << std::format("Moved {} steps to {}\n", steps,
                             buildings[new_pos]->getName());

    // Take action on building landed upon
    auto &building = buildings[new_pos];
    building->processEvent(player);
    return true;
  }
  throw("Failed to acquire player pointer");
  return false;
}
