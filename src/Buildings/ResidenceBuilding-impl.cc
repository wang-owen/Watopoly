#include "../Board.h"
#include "../Player.h"
#include "ResidenceBuilding.h"

const std::vector<std::string> ResidenceBuilding::RESIDENCE_NAMES = {
    "MKV", "UWP", "V1", "REV"};

ResidenceBuilding::ResidenceBuilding(const std::string &name)
    : OwnableBuilding{name, PURCHASE_COST} {}

int ResidenceBuilding::getFee() const {
  if (has_owner) {
    if (auto o = owner.lock()) {
      int fee = 0;
      for (auto &name : RESIDENCE_NAMES) {
        if (o->getProperties().count(name)) {
          fee = (fee == 0) ? 25 : fee * 2;
        }
      }
      return fee;
    }
  }
  return 0;
}