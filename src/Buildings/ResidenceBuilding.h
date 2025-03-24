#ifndef RESIDENCEBUILDING_H
#define RESIDENCEBUILDING_H

#include "OwnableBuilding.h"

class ResidenceBuilding : public OwnableBuilding {
public:
  static const std::vector<std::string> RESIDENCE_NAMES;

  ResidenceBuilding(const std::string &name);

  int getFee() const override;

private:
  static const int PURCHASE_COST = 200;
};

#endif
