#ifndef GYMBUILDING_H
#define GYMBUILDING_H

#include "OwnableBuilding.h"

class GymBuilding : public OwnableBuilding {
public:
  static const std::vector<std::string> GYM_NAMES;

  GymBuilding(const std::string &name);

  int getPurchaseCost() const override;

  int getFee() const override;

private:
  static const int PURCHASE_COST = 150;
  std::string name;
  bool hasOwner;
  std::weak_ptr<Player> owner;
};

#endif
