export module CollectOSAP;

import <iostream>;
import Player;
import UnownableBuilding;

export class CollectOSAP : public UnownableBuilding {
public:
  CollectOSAP() : UnownableBuilding{"COLLECT OSAP"}, OSAP_AMOUNT{200} {}

  void processEvent(const std::shared_ptr<Player> player) override {
    std::cout << "You have collected your OSAP grant of $200\n";
    player->increaseFunds(OSAP_AMOUNT);
    player->displayBalance();
  }

private:
  const int OSAP_AMOUNT;
};

