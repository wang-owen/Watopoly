#ifndef MORTGAGECOMMAND_H
#define MORTGAGECOMMAND_H

#include "Command.h"

class MortgageCommand : public Command {
public:
  static const std::string NAME;

  explicit MortgageCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;

private:
  const int MORTGAGE_PERCENT;
};

#endif