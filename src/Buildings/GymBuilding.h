#ifndef GYMBUILDING_H
#define GYMBUILDING_H

#include "OwnableBuilding.h"

class Player;

class GymBuilding : public OwnableBuilding {
public:
  static const std::vector<std::string> GYM_NAMES;

  GymBuilding(const std::string &name,
              const std::vector<std::shared_ptr<Player>> &players);

  int getFee() const override;

private:
  static const int PURCHASE_COST = 150;
};

#endif
