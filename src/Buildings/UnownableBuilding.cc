export module UnownableBuilding;

import Building;

export class UnownableBuilding : public Building {
public:
  UnownableBuilding(const std::string &name) : Building{name} {}
};

