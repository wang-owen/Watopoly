#ifndef ALLCOMMAND_H
#define ALLCOMMAND_H

#include "Command.h"

class AllCommand : public Command {
public:
  static const std::string NAME;

  explicit AllCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

#endif
