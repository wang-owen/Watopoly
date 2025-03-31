#include <iostream>

#include "../Board.h"
#include "../Dice.h"
#include "../Player.h"
#include "RollUpTheRimDecorator.h"

RollUpTheRimDecorator::RollUpTheRimDecorator(
    std::unique_ptr<UnownableBuilding> building,
    std::shared_ptr<int> active_cups)
    : UnownableBuilding{building->getName()}, building{std::move(building)},
      active_cups{active_cups} {}

void RollUpTheRimDecorator::processEvent(const std::shared_ptr<Player> player) {
  if (active_cups && *active_cups < Board::MAX_CUPS &&
      Dice::getProbability(probability)) {
    player->addCup();
    (*active_cups)++;
    std::cout << "WINNER! You have received a Roll Up THe Rim cup! Use this to "
                 "get out of the DC Tims Line.\n";
  } else {
    building->processEvent(player);
  }
}
