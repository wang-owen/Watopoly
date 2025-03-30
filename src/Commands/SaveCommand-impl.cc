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

void SaveCommand::execute(const std::vector<std::string> &params) {
    auto ctx = context.lock();
    if (!ctx) {
        return;
    }
    std::string filename = params[0];
    if (!filename.ends_with(".txt")) {
        filename += ".txt";
    }
    std::ofstream savefile(filename);

    savefile << ctx->players.size() << std::endl;

    for (int i = ctx->cur_player_idx; i < ctx->players.size(); i++) {
        auto player = ctx->players[i];
        savefile << player->getName() << " " << player->getPiece() << " " << player->getCups() << " "
                 << player->getBalance() << " " << player->getPosition();
        if (player->getPosition() == 10) {
            if (player->getTurnsInTims()) {
                savefile << "1 " << player->getTurnsInTims() - 1 << "\n";
            } else {
                savefile << " 0";
            }
        }
    }
    for (int i = 0; i < ctx->cur_player_idx; i++) {
        auto player = ctx->players[i];
        savefile << player->getName() << " " << player->getPiece() << " " << player->getCups() << " "
                 << player->getBalance() << " " << player->getPosition();
        
        if (player->getPosition() == 10) {
            if (player->getTurnsInTims()) {
                savefile << "1 " << player->getTurnsInTims() - 1 << "\n";
            } else {
                savefile << " 0";
            }
        }
        savefile << "\n";
    }
    // for (auto &player : ctx->players) {
    //     savefile << player->getName() << " " << player->getPiece() << " " << player->getCups() << " "
    //              << player->getBalance() << " " << player->getPosition();
    //     if (player->getTurnsInTims()) {
    //         savefile << "1 " << player->getTurnsInTims() - 1 << "\n";
    //     } else {
    //         savefile << " 0\n";
    //     }
    // }

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
            savefile << "0\n";
        }
    }
    savefile.close();
}

