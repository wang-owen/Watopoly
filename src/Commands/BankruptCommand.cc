export module BankruptCommand;

import Command;

class OwnableBuilding;

export class BankruptCommand : public Command {
public:
  static const std::string NAME;

  explicit BankruptCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> & /*params*/ = {}) override;
};

