module GymBuilding;

import Dice;
import Player;

const std::vector<std::string> GymBuilding::GYM_NAMES = {"PAC", "CIF"};

GymBuilding::GymBuilding(const std::string &name,
                         const std::vector<std::shared_ptr<Player>> &players)
    : OwnableBuilding{name, PURCHASE_COST, players} {}

int GymBuilding::getFee() const {
  if (has_owner) {
    int fee = 0;
    for (auto n : Dice::roll(6, 2)) {
      fee += n;
    }
    auto &properties = owner->getProperties();
    if (properties.count(GYM_NAMES[0]) && properties.count(GYM_NAMES[1])) {
      return fee * 10;
    }
    return fee * 4;
  }
  return 0;
}
