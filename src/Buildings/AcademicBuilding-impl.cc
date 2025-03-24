#include "AcademicBuilding.h"

AcademicBuilding::AcademicBuilding(const std::string &name, MonopolyBlock block,
                                   int purchase_cost, int improvement_cost,
                                   const std::array<int, 6> &tuition)
    : OwnableBuilding{name, purchase_cost}, block{block},
      improvement_cost{improvement_cost}, tuition{tuition},
      num_improvements{0} {}

int AcademicBuilding::getFee() const { return tuition[num_improvements]; }

int AcademicBuilding::getImprovementCost() const { return improvement_cost; }

MonopolyBlock AcademicBuilding::getBlock() const { return block; }