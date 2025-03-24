#ifndef OWNABLEBUILDING_H
#define OWNABLEBUILDING_H

#include "Building.h"

class Player;

class OwnableBuilding : public Building {
public:
  OwnableBuilding(const std::string &name, int purchase_cost);

  int getPurchaseCost() const;

  virtual int getFee() const = 0;

protected:
  int purchase_cost;
  bool has_owner;
  std::weak_ptr<Player> owner;
};

#endif
