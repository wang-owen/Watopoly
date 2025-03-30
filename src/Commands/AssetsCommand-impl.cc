#include <format>
#include <iostream>
#include <sstream>

#include "AssetsCommand.h"
#include "CommandContext.h"

const std::string AssetsCommand::NAME = "assets";

AssetsCommand::AssetsCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

void AssetsCommand::execute(const std::vector<std::string> & /*params*/) {
  if (auto ctx = context.lock()) {
    ctx->cur_player->displayAssets();
    return;
  }
  throw("Failed to acquire player pointer");
}
