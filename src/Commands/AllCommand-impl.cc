#include <format>
#include <iostream>
#include <sstream>

#include "AllCommand.h"
#include "CommandContext.h"

const std::string AllCommand::NAME = "all";

AllCommand::AllCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

void AllCommand::execute(const std::vector<std::string> & /*params*/) {
  if (auto ctx = context.lock()) {
    for (auto &player : ctx->players) {
      player->displayAssets();
    }
  } else {
    throw("Failed to acquire player pointer");
  }
}
