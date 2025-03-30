#ifndef OWNABLEBUILDING_H
#define OWNABLEBUILDING_H

#include "Building.h"

class Player;

class OwnableBuilding : public Building,
                        public std::enable_shared_from_this<OwnableBuilding> {
public:
  OwnableBuilding(const std::string &name, int cost);

  int getCost() const;

  bool hasOwner() const;

  void setOwner(std::shared_ptr<Player> player);

  std::shared_ptr<Player> getOwner() const;

  virtual int getFee() const = 0;

  void processEvent(const std::shared_ptr<Player> &player) override;

protected:
  int cost;
  bool has_owner;
  std::weak_ptr<Player> owner;
};

#endif
