export module SaveCommand;

import Command;

export class SaveCommand : public Command {
public:
  static const std::string NAME;

  explicit SaveCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;
};

