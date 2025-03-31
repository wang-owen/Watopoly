export module RollUpTheRimDecorator;

import UnownableBuilding;

export class RollUpTheRimDecorator : public UnownableBuilding {
public:
  RollUpTheRimDecorator(std::unique_ptr<UnownableBuilding> building,
                        std::shared_ptr<int> active_cups);

  void processEvent(const std::shared_ptr<Player> player) override;

private:
  std::unique_ptr<UnownableBuilding> building;
  const double probability = 0.01;
  std::shared_ptr<int> active_cups;
};

