#include "../Dice.h"
#include "../Player.h"
#include "GymBuilding.h"

const std::vector<std::string> GymBuilding::GYM_NAMES = {"PAC", "CIF"};

GymBuilding::GymBuilding(const std::string &name)
    : OwnableBuilding{name, PURCHASE_COST} {}

int GymBuilding::getFee() const {
  if (has_owner) {
    if (auto o = owner.lock()) {
      Dice dice{6};
      int fee = 0;
      for (auto n : dice.roll(2)) {
        fee += n;
      }
      auto &properties = o->getProperties();
      if (properties.contains(GYM_NAMES[0]) &&
          properties.contains(GYM_NAMES[1])) {
        return fee * 10;
      }
      return fee * 4;
    }
  }
  return 0;
}