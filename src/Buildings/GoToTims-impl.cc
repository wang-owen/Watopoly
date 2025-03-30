#include "GoToTims.h"
#include "Player.h"

GoToTims::GoToTims(const std::vector<std::shared_ptr<Building>> &buildings)
    : UnownableBuilding{"GO TO TIMS"}, buildings{buildings} {}

void GoToTims::processEvent(const std::shared_ptr<Player> &player) {
  player->setTurnsInTims(1);
  player->moveToIdx(10, buildings);
}
