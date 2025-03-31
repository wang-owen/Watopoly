export module RollCommand;

import Command;

export class RollCommand : public Command {
public:
  static const std::string NAME;

  explicit RollCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params = {}) override;
};

