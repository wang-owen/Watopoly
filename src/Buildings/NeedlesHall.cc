export module NeedlesHall;

import UnownableBuilding;

export class NeedlesHall : public UnownableBuilding {
public:
  NeedlesHall();

  void processEvent(const std::shared_ptr<Player> player) override;
};

