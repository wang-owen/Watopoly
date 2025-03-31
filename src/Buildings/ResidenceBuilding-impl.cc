#include "../Board.h"
#include "../Player.h"
#include "ResidenceBuilding.h"

const std::vector<std::string> ResidenceBuilding::RESIDENCE_NAMES = {
    "MKV", "UWP", "V1", "REV"};

ResidenceBuilding::ResidenceBuilding(
    const std::string &name,
    const std::vector<std::shared_ptr<Player>> &players)
    : OwnableBuilding{name, PURCHASE_COST, players} {}

int ResidenceBuilding::getFee() const {
  if (has_owner) {
    int fee = 0;
    for (auto &name : RESIDENCE_NAMES) {
      if (owner->getProperties().count(name)) {
        fee = (fee == 0) ? 25 : fee * 2;
      }
    }
    return fee;
  }
  return 0;
}