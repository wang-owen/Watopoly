#include <iostream>
#include <sstream>
#include <fstream> 

#include "CommandContext.h"
#include "SaveCommand.h"
#include "../Buildings/Building.h"
#include "../Buildings/AcademicBuilding.h"
#include "../Buildings/ResidenceBuilding.h"
#include "../Buildings/GymBuilding.h"

const std::string SaveCommand::NAME = "save";

SaveCommand::SaveCommand(std::weak_ptr<CommandContext> context)
    : Command{context} {}

bool SaveCommand::execute(std::vector<std::string> params) {
    auto ctx = context.lock();
    if (!ctx) {
        return false;
    }
    std::string filename = params[0];
    if (!filename.ends_with(".txt")) {
        filename += ".txt";
    }
    std::ofstream savefile(filename);

    savefile << ctx->players.size() << std::endl;
    for (auto &player : ctx->players) {
        // TODO add TimsCups when that implemention is complete
        // TODO implement DC Tims Line position
        /*  
        If a player is on square 10 (DC Tims Line), their line will look
        like one of the following:
        player char TimsCups money 10 0
        player char TimsCups money 10 1 num
        The first line represents that the player’s position is the DC Tims Line but they are not actually in the DC Tims Line. The
        second line represents the player is in the DC Tims line and num is the number of turns they’ve been there. The value of num
        must be between 0 and 2, inclusive
        */
        savefile << player->getName() << " " << player->getPiece() << " "
                 << player->getBalance() << " " << player->getPosition() << std::endl;
    }

    for (auto building : ctx->board->getBuildings()) {
        if (auto b = std::dynamic_pointer_cast<AcademicBuilding>(building)) {
            savefile << b->getName() << " "; 
            if (b->hasOwner()) {
                savefile << b->getOwner()->getName() << " ";
            } else {
                savefile << "BANK ";
            } 
            savefile << b->getNumImprovements() << std::endl;
        } else if (auto b = std::dynamic_pointer_cast<ResidenceBuilding>(building)) {
            savefile << b->getName() << " ";
            if (b->hasOwner()) {
                savefile << b->getOwner()->getName() << " ";
            } else {
                savefile << "BANK ";
            }  
            savefile << "0" << std::endl;
        } else if (auto b = std::dynamic_pointer_cast<GymBuilding>(building)) {
            savefile << b->getName() << " ";
            if (b->hasOwner()) {
                savefile << b->getOwner()->getName() << " ";
            } else {
                savefile << "BANK ";
            }  
            savefile << "0" << std::endl;
        }
    }
    savefile.close();
    return true;
}

