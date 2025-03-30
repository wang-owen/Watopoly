#ifndef DCTIMSLINE_H
#define DCTIMSLINE_H

#include "UnownableBuilding.h"

class DCTimsLine : public UnownableBuilding {
public:
  DCTimsLine() : UnownableBuilding{"DC TIMS LINE"} {}
  
  void processEvent(const std::shared_ptr<Player> &player) {}
};

#endif
