#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

struct CommandContext;

class Command {
public:
  Command(std::weak_ptr<CommandContext> context);

  virtual bool execute() = 0;

protected:
  std::weak_ptr<CommandContext> context;
};

#endif