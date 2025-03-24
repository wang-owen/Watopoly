#include "../Board.h"
#include "../Buildings/Building.h"
#include "../Dice.h"
#include "RollCommand.h"

const std::string RollCommand::NAME = "roll";

RollCommand::RollCommand(std::weak_ptr<Board> board) : board{board} {}

bool RollCommand::execute(std::shared_ptr<Player> player,
                          const std::vector<std::string> &params = {}) {
  Dice dice{6};
  int steps = 0;
  for (auto n : dice.roll(2)) {
    steps += n;
  }
  if (auto b = board.lock()) {
    auto &buildings = b->getBuildings();
    auto buildings_size = static_cast<int>(buildings.size());
    int curPos = player->getPosition();
    int newPos = (curPos + steps < buildings_size)
                     ? curPos + steps
                     : curPos + steps - buildings_size;
    player->setPosition(newPos);
    buildings[curPos]->removePiece(player->getPiece());
    buildings[newPos]->addPiece(player->getPiece());

    return true;
  }
  return false;
}