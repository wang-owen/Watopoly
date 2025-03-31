#include <fstream>
#include <iostream>
#include <sstream>

#include "../Buildings/AcademicBuilding.h"
#include "../Buildings/Building.h"
#include "../Buildings/GymBuilding.h"
#include "../Buildings/ResidenceBuilding.h"
#include "CommandContext.h"
#include "SaveCommand.h"

const std::string SaveCommand::NAME = "save";

SaveCommand::SaveCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void SaveCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 1) {
    std::cout << "Usage: save <filename>\n";
    return;
  }

  std::string filename = params[0];
  if (!filename.ends_with(".txt")) {
    filename += ".txt";
  }
  std::ofstream savefile(filename);

  savefile << context->players.size() << "\n";

  for (int i = context->cur_player_idx; i < context->players.size(); i++) {
    auto player = context->players[i];
    savefile << player->getName() << " " << player->getPiece() << " "
             << player->getCups() << " " << player->getBalance() << " "
             << player->getPosition();
    if (player->getPosition() == 10) {
      if (player->getTurnsInTims()) {
        savefile << "1 " << player->getTurnsInTims() - 1;
      } else {
        savefile << " 0";
      }
    }
    savefile << "\n";
  }
  for (int i = 0; i < context->cur_player_idx; i++) {
    auto player = context->players[i];
    savefile << player->getName() << " " << player->getPiece() << " "
             << player->getCups() << " " << player->getBalance() << " "
             << player->getPosition();

    if (player->getPosition() == 10) {
      if (player->getTurnsInTims()) {
        savefile << "1 " << player->getTurnsInTims() - 1;
      } else {
        savefile << " 0";
      }
    }
    savefile << "\n";
  }

  for (auto &building : context->board->getBuildings()) {
    if (auto b = std::dynamic_pointer_cast<AcademicBuilding>(building)) {
      savefile << b->getName() << " ";
      if (b->hasOwner()) {
        savefile << b->getOwner()->getName() << " ";
      } else {
        savefile << "BANK ";
      }
      if (b->isMortgaged()) {
        savefile << "-1\n";
      } else {
        savefile << b->getNumImprovements() << "\n";
      }
    } else if (auto b =
                   std::dynamic_pointer_cast<ResidenceBuilding>(building)) {
      savefile << b->getName() << " ";
      if (b->hasOwner()) {
        savefile << b->getOwner()->getName() << " ";
      } else {
        savefile << "BANK ";
      }
      if (b->isMortgaged()) {
        savefile << "-1\n";
      } else {
        savefile << "0\n";
      }
    } else if (auto b = std::dynamic_pointer_cast<GymBuilding>(building)) {
      savefile << b->getName() << " ";
      if (b->hasOwner()) {
        savefile << b->getOwner()->getName() << " ";
      } else {
        savefile << "BANK ";
      }
      if (b->isMortgaged()) {
        savefile << "-1\n";
      } else {
        savefile << "0\n";
      }
    }
  }
  savefile.close();

  std::cout << "Successfully saved to " << filename << "\n";
}
