#include "OwnableBuilding.h"

OwnableBuilding::OwnableBuilding(const std::string &name, int cost)
    : Building{name}, cost{cost}, has_owner{false} {}

int OwnableBuilding::getCost() const { return cost; }

bool OwnableBuilding::hasOwner() const { return has_owner; }

void OwnableBuilding::setOwner(std::shared_ptr<Player> player) {
  owner = player;
  has_owner = player ? true : false;
}

std::shared_ptr<Player> OwnableBuilding::getOwner() const {
  if (auto o = owner.lock()) {
    return o;
  }
  return nullptr;
}