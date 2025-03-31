export module SLC;

import UnownableBuilding;

export class SLC : public UnownableBuilding {
public:
  SLC(const std::vector<std::shared_ptr<Building>> &buildings);

  void processEvent(const std::shared_ptr<Player> player) override;

private:
  const std::vector<std::shared_ptr<Building>> &buildings;
};

