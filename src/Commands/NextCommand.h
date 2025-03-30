#ifndef NEXTCOMMAND_H
#define NEXTCOMMAND_H

#include "Command.h"

class NextCommand : public Command {
public:
  static const std::string NAME;

  explicit NextCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

#endif