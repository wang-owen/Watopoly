export module Tuition;

import UnownableBuilding;

export class Tuition : public UnownableBuilding {
public:
  Tuition();

  void processEvent(const std::shared_ptr<Player> player) override;
private:
  const int TUITION_AMOUNT;
  const double PERCENT_AMOUNT;
};

