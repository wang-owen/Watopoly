#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "OwnableBuilding.h"

enum class MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class Player;

class AcademicBuilding : public OwnableBuilding {
public:
  AcademicBuilding(const std::string &name, MonopolyBlock block,
                   int purchase_cost, int improvement_cost,
                   const std::array<int, 6> &tuition);

  int getFee() const override;

  int getImprovementCost() const;

  MonopolyBlock getBlock() const;

private:
  MonopolyBlock block;
  int improvement_cost;
  std::array<int, 6> tuition;
  int num_improvements;
};

#endif