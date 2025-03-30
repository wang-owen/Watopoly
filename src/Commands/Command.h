#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>
#include <vector>

struct CommandContext;

class Command {
public:
  Command(std::shared_ptr<CommandContext> context);

  virtual ~Command() = default;

  virtual void execute(const std::vector<std::string> &params = {}) = 0;

protected:
  std::shared_ptr<CommandContext> context;
};

#endif