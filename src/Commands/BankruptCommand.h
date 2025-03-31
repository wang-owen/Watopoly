#ifndef BANKRUPT_H
#define BANKRUPT_H

#include "Command.h"

class OwnableBuilding;

class BankruptCommand : public Command {
public:
  static const std::string NAME;

  explicit BankruptCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

#endif