#include "OwnableBuilding.h"

OwnableBuilding::OwnableBuilding(const std::string &name, int purchase_cost)
    : Building{name}, purchase_cost{purchase_cost}, has_owner{false} {}

int OwnableBuilding::getPurchaseCost() const { return purchase_cost; }
