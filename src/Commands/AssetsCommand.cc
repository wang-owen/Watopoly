export module AssetsCommand;

import Command;

export class AssetsCommand : public Command {
public:
  static const std::string NAME;

  explicit AssetsCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

