#include <format>
#include <iostream>
#include <sstream>

#include "CommandContext.h"
#include "AllCommand.h"

const std::string AllCommand::NAME = "all";

AllCommand::AllCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool AllCommand::execute(std::vector<std::string> params) {
    auto ctx = context.lock();
    if (!ctx) {
        return false;
    }
    for (auto &player : ctx->players) {
        std::cout << std::format("Assets for {}:\n", player->getName());
        std::cout << "----------------\n";
        std::cout << std::format("Cash: ${}\n", player->getBalance());
        std::cout << "Properties:\n";
        for (auto &property : player->getProperties()) {
            std::cout << std::format("- {}\n", property.first);
        }
    }
    return true;
}
