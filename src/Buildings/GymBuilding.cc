export module GymBuilding;

import OwnableBuilding;
import Player;

export class GymBuilding : public OwnableBuilding {
public:
  static const std::vector<std::string> GYM_NAMES;

  GymBuilding(const std::string &name,
              const std::vector<std::shared_ptr<Player>> &players);

  int getFee() const override;

private:
  static const int PURCHASE_COST = 150;
};
