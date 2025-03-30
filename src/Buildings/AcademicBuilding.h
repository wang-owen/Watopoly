#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "OwnableBuilding.h"

enum class MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class Player;

class AcademicBuilding : public OwnableBuilding {
public:
  AcademicBuilding(const std::string &name, MonopolyBlock block,
                   int purchase_cost, int improvement_cost,
                   const std::array<int, 6> &tuition)
      : OwnableBuilding{name, purchase_cost}, block{block},
        improvement_cost{improvement_cost}, tuition{tuition},
        num_improvements{0} {}

  static const int MAX_IMPROVEMENTS = 5;

  static std::vector<std::string> getBlockBuildings(MonopolyBlock block) {
    switch (block) {
    case MonopolyBlock::Arts1:
      return {"AL", "ML"};
    case MonopolyBlock::Arts2:
      return {"ECH", "PAS", "HH"};
    case MonopolyBlock::Eng:
      return {"RCH", "DWE", "CPH"};
    case MonopolyBlock::Health:
      return {"LHI", "BMH", "OPT"};
    case MonopolyBlock::Env:
      return {"EV1", "EV2", "EV3"};
    case MonopolyBlock::Sci1:
      return {"B1", "B2"};
    case MonopolyBlock::Sci2:
      return {"EIT", "ESC", "C2"};
    case MonopolyBlock::Math:
      return {"MC", "DC"};
    default:
      return {};
    }
  }

  int getFee() const override { return tuition[num_improvements]; }

  int getImprovementCost() const { return improvement_cost; }

  int getNumImprovements() const { return num_improvements; }

  MonopolyBlock getBlock() const { return block; }

private:
  MonopolyBlock block;
  int improvement_cost;
  std::array<int, 6> tuition;
  int num_improvements;
};

#endif