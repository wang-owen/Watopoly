#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "OwnableBuilding.h"

enum class MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class Player;

class AcademicBuilding : public OwnableBuilding {
public:
  AcademicBuilding(const std::string &name, MonopolyBlock block,
                   int purchaseCost, int improvementCost,
                   const std::array<int, 6> &tuition);

  int getPurchaseCost() const override;

  int getFee() const override;

  int getImprovementCost() const;

  MonopolyBlock getBlock() const;

private:
  std::string name;
  MonopolyBlock block;
  int purchaseCost, improvementCost;
  std::array<int, 6> tuition;
  int numImprovements;
  bool hasOwner;
  std::weak_ptr<Player> owner;
};

#endif