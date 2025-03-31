module AllCommand;

import <iostream>;
import <sstream>;
import CommandContext;

const std::string AllCommand::NAME = "all";

AllCommand::AllCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void AllCommand::execute(const std::vector<std::string> & /*params*/) {
  for (auto &player : context->players) {
    if (!player->isActive()) {
      continue;
    }
    player->displayAssets();
  }
}
