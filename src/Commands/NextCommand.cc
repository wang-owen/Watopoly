export module NextCommand;

import Command;

export class NextCommand : public Command {
public:
  static const std::string NAME;

  explicit NextCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

