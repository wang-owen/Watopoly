#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "Command.h"

class SaveCommand : public Command {
public:
  static const std::string NAME;

  explicit SaveCommand(std::weak_ptr<CommandContext> context);

  bool execute(std::vector<std::string> params) override;
};

#endif