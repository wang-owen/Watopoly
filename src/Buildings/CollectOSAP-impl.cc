#include "../Player.h"
#include "CollectOSAP.h"

CollectOSAP::CollectOSAP() : UnownableBuilding{"COLLECT OSAP"} {}

void CollectOSAP::processEvent(const std::shared_ptr<Player> &player) {
  player->increaseFunds(OSAP_AMOUNT);
}