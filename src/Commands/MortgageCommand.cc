export module MortgageCommand;

import Command;

export class MortgageCommand : public Command {
public:
  static const std::string NAME;

  explicit MortgageCommand(std::shared_ptr<CommandContext> context);

  void execute(const std::vector<std::string> &params) override;

private:
  const double MORTGAGE_PERCENT;
};

