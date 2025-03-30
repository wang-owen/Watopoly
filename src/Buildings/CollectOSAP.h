#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H

#include "UnownableBuilding.h"

class CollectOSAP : public UnownableBuilding {
public:
  CollectOSAP();

  void processEvent(const std::shared_ptr<Player> &player) override;

private:
  static const int OSAP_AMOUNT = 200;
};

#endif
