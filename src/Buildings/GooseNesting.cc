export module GooseNesting;

import Player;
import UnownableBuilding;

export class GooseNesting : public UnownableBuilding {
public:
  GooseNesting() : UnownableBuilding{"GOOSE NESTING"} {}

  void processEvent(const std::shared_ptr<Player> player) {
    std::cout << player->getName()
              << " has disturbed a flock of nesting geese!\n";
    std::cout << "The geese honk angrily and flap their wings, but do no real "
                 "harm.\n";
    std::cout << player->getName()
              << " escapes unscathed, but slightly shaken.\n";
  }
};

