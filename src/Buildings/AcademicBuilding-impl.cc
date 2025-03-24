#include "AcademicBuilding.h"

AcademicBuilding::AcademicBuilding(const std::string &name, MonopolyBlock block,
                                   int purchaseCost, int improvementCost,
                                   const std::array<int, 6> &tuition)
    : OwnableBuilding{}, name{name}, block{block}, purchaseCost{purchaseCost},
      improvementCost{improvementCost}, tuition{tuition}, numImprovements{0},
      hasOwner{false} {}

int AcademicBuilding::getPurchaseCost() const { return purchaseCost; }

int AcademicBuilding::getFee() const { return tuition[numImprovements]; }

int AcademicBuilding::getImprovementCost() const { return improvementCost; }

MonopolyBlock AcademicBuilding::getBlock() const { return block; }