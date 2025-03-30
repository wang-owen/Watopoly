#include "../Dice.h"
#include "../Player.h"
#include "GymBuilding.h"

const std::vector<std::string> GymBuilding::GYM_NAMES = {"PAC", "CIF"};

GymBuilding::GymBuilding(const std::string &name)
    : OwnableBuilding{name, PURCHASE_COST} {}

int GymBuilding::getFee() const {
  if (has_owner) {
    if (auto o = owner.lock()) {
      int fee = 0;
      for (auto n : Dice::roll(6, 2)) {
        fee += n;
      }
      auto &properties = o->getProperties();
      if (properties.count(GYM_NAMES[0]) &&
          properties.count(GYM_NAMES[1])) {
        return fee * 10;
      }
      return fee * 4;
    }
  }
  return 0;
}