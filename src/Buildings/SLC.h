#ifndef SLC_H
#define SLC_H

#include "UnownableBuilding.h"

class SLC : public UnownableBuilding {
public:
  SLC(const std::vector<std::shared_ptr<Building>> &buildings);

  void processEvent(const std::shared_ptr<Player> player) override;

private:
  const std::vector<std::shared_ptr<Building>> &buildings;
};

#endif
