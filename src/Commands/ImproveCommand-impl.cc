#include <format>
#include <iostream>
#include <sstream>

#include "CommandContext.h"
#include "ImproveCommand.h"
#include "../Buildings/OwnableBuilding.h"
#include "../Buildings/AcademicBuilding.h"
#include "../Player.h"

const std::string ImproveCommand::NAME = "improve";

ImproveCommand::ImproveCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void ImproveCommand::execute(const std::vector<std::string> &params) {
    if (params.size() != 2 || (params[1] != "buy" && params[1] != "sell")) {
        std::cout << "Invalid command. Usage: improve <property> <buy/sell>\n";
        return;
    }
    auto &player = context->cur_player;
    std::string property_name = params[0];
    auto &player_properties = player->getProperties();
    if (!player_properties.contains(property_name)) {
        std::cout << std::format("{} does not own {}!\n", player->getName(), property_name);
        return;
    }
    if (!(std::dynamic_pointer_cast<AcademicBuilding>(player_properties.at(property_name)))) {
        std::cout << "That building cannot have improvements!\n";
        return;
    } 
    
    auto academic_building = std::dynamic_pointer_cast<AcademicBuilding>(player_properties.at(property_name));
    if (params[1] == "buy") {
        if (academic_building->getNumImprovements() == AcademicBuilding::MAX_IMPROVEMENTS) {
            std::cout << "This building already has the maximum number of improvements!\n";
            return;
        }

        for (auto &block_property : academic_building->getBlockBuildings(academic_building->getBlock())) {
            if (!player_properties.contains(block_property)) {
                std::cout << "You do not own all properties in this block!\n";
                return;
            }
        }
        if (player->getBalance() < academic_building->getImprovementCost()) {
            std::cout << "You do not have enough funds to buy an improvement!\n";
            return;
        }
        academic_building->addImprovement();
        player->reduceFunds(academic_building->getImprovementCost());
        std::cout << "Improvement bought!\n";
        return;
    } else if (params[1] == "sell") {
        if (academic_building->getNumImprovements() == 0) {
            std::cout << "This building doesn't have any improvements!\n";
            return;
        }
        academic_building->removeImprovement();
        player->increaseFunds(academic_building->getImprovementCost() / 2);
        std::cout << "Improvement sold!\n";
        return;
    }
}
