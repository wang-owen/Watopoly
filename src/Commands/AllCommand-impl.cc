#include <iostream>
#include <sstream>

#include "AllCommand.h"
#include "CommandContext.h"

const std::string AllCommand::NAME = "all";

AllCommand::AllCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void AllCommand::execute(const std::vector<std::string> & /*params*/) {
  for (auto &player : context->players) {
    player->displayAssets();
  }
}
