#include <format>
#include <iostream>
#include <sstream>

#include "CommandContext.h"
#include "AssetsCommand.h"

const std::string AssetsCommand::NAME = "assets";

AssetsCommand::AssetsCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool AssetsCommand::execute(std::vector<std::string> params) {
    auto ctx = context.lock();
    if (!ctx) {
        return false;
    }

    auto &cur_player = ctx->cur_player;
    std::cout << std::format("Assets for {}:\n", cur_player->getName());
    std::cout << "----------------\n";
    std::cout << std::format("Cash: ${}\n", cur_player->getBalance());
    std::cout << "Properties:\n";
    for (auto &property : cur_player->getProperties()) {
        std::cout << std::format("- {}\n", property.first);
    }
    return true;
}
