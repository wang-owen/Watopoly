#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H

#include "UnownableBuilding.h"

class NeedlesHall : public UnownableBuilding {
public:
  NeedlesHall();

  void processEvent(const std::shared_ptr<Player> player) override;
};

#endif
