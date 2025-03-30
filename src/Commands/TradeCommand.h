#ifndef TRADECOMMAND_H
#define TRADECOMMAND_H

#include "../Buildings/AcademicBuilding.h"
#include "Command.h"

class OwnableBuilding;

class TradeCommand : public Command {
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

#endif