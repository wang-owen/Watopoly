#ifndef NEXTCOMMAND_H
#define NEXTCOMMAND_H

#include "Command.h"

class NextCommand : public Command {
public:
  static const std::string NAME;

  explicit NextCommand(std::weak_ptr<CommandContext> context);

  bool execute() override;
};

#endif