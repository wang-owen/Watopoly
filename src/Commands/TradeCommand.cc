export module TradeCommand;

import AcademicBuilding;
import Command;
import OwnableBuilding;

export class TradeCommand : public Command {
public:
  static const std::string NAME;

  explicit TradeCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;

private:
  bool playerMonopolyHasImprovements(
      const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>>
          &properties,
      MonopolyBlock block) const;
};
