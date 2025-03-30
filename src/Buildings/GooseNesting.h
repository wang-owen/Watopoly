#ifndef GOOSENESTING_H
#define GOOSENESTING_H

#include "../Player.h"
#include "UnownableBuilding.h"

class GooseNesting : public UnownableBuilding {
public:
  GooseNesting() : UnownableBuilding{"GOOSE NESTING"} {}

  void processEvent(const std::shared_ptr<Player> &player) {
    std::cout << player->getName()
              << " has disturbed a flock of nesting geese!\n";
    std::cout << "The geese honk angrily and flap their wings, but do no real "
                 "harm.\n";
    std::cout << player->getName()
              << " escapes unscathed, but slightly shaken.\n";
  }
};

#endif
