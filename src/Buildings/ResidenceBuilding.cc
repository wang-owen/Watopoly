export module ResidenceBuilding;

import OwnableBuilding;
import Player;

export class ResidenceBuilding : public OwnableBuilding {
public:
  static const std::vector<std::string> RESIDENCE_NAMES;

  ResidenceBuilding(const std::string &name,
                    const std::vector<std::shared_ptr<Player>> &players);

  int getFee() const override;

private:
  static const int PURCHASE_COST = 200;
};

