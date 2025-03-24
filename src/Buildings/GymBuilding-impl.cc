#include "../Dice.h"
#include "GymBuilding.h"
#include "../Player.h"

const std::vector<std::string> GymBuilding::GYM_NAMES = {"PAC", "CIF"};

GymBuilding::GymBuilding(const std::string &name) : name{name} {}

int GymBuilding::getPurchaseCost() const { return PURCHASE_COST; }

int GymBuilding::getFee() const {
  if (hasOwner) {
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