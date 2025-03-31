#ifndef ROLLCOMMAND_H
#define ROLLCOMMAND_H

#include "Command.h"

class RollCommand : public Command {
public:
  static const std::string NAME;

  explicit RollCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params = {}) override;
};

#endif
