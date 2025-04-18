#ifndef UNMORTGAGECOMMAND_H
#define UNMORTGAGECOMMAND_H

#include "Command.h"

class UnmortgageCommand : public Command {
public:
  static const std::string NAME;

  explicit UnmortgageCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;

private:
  const double UNMORTGAGE_PERCENT;
};

#endif
