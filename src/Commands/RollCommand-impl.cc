#include <format>
#include <iostream>

#include "../Buildings/Building.h"
#include "../Dice.h"
#include "CommandContext.h"
#include "RollCommand.h"

const std::string RollCommand::NAME = "roll";

RollCommand::RollCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool RollCommand::execute() {
  if (auto ctx = context.lock()) {
    Dice dice{6};
    int steps = 0;
    for (auto n : dice.roll(2)) {
      steps += n;
    }
    auto &buildings = ctx->board->getBuildings();
    auto &player = ctx->cur_player;
    auto buildings_size = static_cast<int>(buildings.size());

    int curPos = player->getPosition();
    int newPos = (curPos + steps < buildings_size)
                     ? curPos + steps
                     : curPos + steps - buildings_size;

    player->setPosition(newPos);
    buildings[curPos]->removePiece(player->getPiece());
    buildings[newPos]->addPiece(player->getPiece());

    std::cout << std::format("Moved {} steps to {}\n", steps,
                             buildings[newPos]->getName());

    return true;
  }
  return false;
}