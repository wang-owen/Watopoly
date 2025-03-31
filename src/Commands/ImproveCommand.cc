module ImproveCommand;

import Command;

export class ImproveCommand : public Command {
public:
  static const std::string NAME;

  explicit ImproveCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;
};

