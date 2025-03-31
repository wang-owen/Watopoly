#ifndef OWNABLEBUILDING_H
#define OWNABLEBUILDING_H

#include "Building.h"

class Player;

class OwnableBuilding : public Building,
                        public std::enable_shared_from_this<OwnableBuilding> {
public:
  OwnableBuilding(const std::string &name, int cost,
                  const std::vector<std::shared_ptr<Player>> &players);

  int getCost() const;

  bool hasOwner() const;

  void setOwner(const std::shared_ptr<Player> player);

  std::shared_ptr<Player> getOwner() const;

  virtual int getFee() const = 0;

  void toggleMortgaged();

  bool isMortgaged() const;

  void auctionProperty(const std::shared_ptr<Player> player,
                       std::vector<std::shared_ptr<Player>> players);

  void processEvent(const std::shared_ptr<Player> player) override;

protected:
  const int cost;
  bool has_owner, mortgaged;
  std::shared_ptr<Player> owner;

private:
  const std::vector<std::shared_ptr<Player>> &players;
};

#endif
