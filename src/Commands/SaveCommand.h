#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "Command.h"

class SaveCommand : public Command {
public:
  static const std::string NAME;

  explicit SaveCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;
};

#endif