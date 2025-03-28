#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>
#include <vector>

struct CommandContext;

class Command {
public:
  Command(std::weak_ptr<CommandContext> context);

  virtual bool execute(std::vector<std::string> params) = 0;

protected:
  std::weak_ptr<CommandContext> context;
};

#endif