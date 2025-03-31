export module Command;

import <memory>;
import <string>;
import <vector>;

struct CommandContext;

export class Command {
public:
  Command(std::shared_ptr<CommandContext> context);

  virtual ~Command() = default;

  virtual void execute(const std::vector<std::string> &params = {}) = 0;

protected:
  std::shared_ptr<CommandContext> context;
};

