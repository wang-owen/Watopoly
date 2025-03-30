#ifndef DCTIMSLINE_H
#define DCTIMSLINE_H

#include "UnownableBuilding.h"

class DCTimsLine : public UnownableBuilding {
public:
  DCTimsLine();

  void processEvent(const std::shared_ptr<Player> &player) override;

private:
  static const int FEE_AMOUNT = 50;
};

#endif
