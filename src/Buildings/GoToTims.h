#ifndef GOTOTIMS_H
#define GOTOTIMS_H

#include "UnownableBuilding.h"

class GoToTims : public UnownableBuilding {
public:
  GoToTims(const std::vector<std::shared_ptr<Building>> &buildings);

  void processEvent(const std::shared_ptr<Player> &player) override;

private:
  const std::vector<std::shared_ptr<Building>> &buildings;
};

#endif
