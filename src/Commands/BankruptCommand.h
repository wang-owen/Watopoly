#ifndef BANKRUPT_H
#define BANKRUPT_H

#include "Command.h"

class BankruptCommand : public Command {
public:
  static const std::string NAME;

  explicit BankruptCommand(std::weak_ptr<CommandContext> context);

  bool execute(std::vector<std::string> params = {}) override;
};

#endif