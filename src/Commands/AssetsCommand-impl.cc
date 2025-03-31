#include <iostream>
#include <sstream>

#include "AssetsCommand.h"
#include "CommandContext.h"

const std::string AssetsCommand::NAME = "assets";

AssetsCommand::AssetsCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void AssetsCommand::execute(const std::vector<std::string> & /*params*/) {
  context->cur_player->displayAssets();
}
