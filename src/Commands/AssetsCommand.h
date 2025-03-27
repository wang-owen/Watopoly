#ifndef ASSETSCOMMAND_H
#define ASSETSCOMMAND_H

#include "Command.h"

class AssetsCommand : public Command {
public:
  static const std::string NAME;

  explicit AssetsCommand(std::weak_ptr<CommandContext> context);

  bool execute() override;
};

#endif