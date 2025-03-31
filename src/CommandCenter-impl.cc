#include <iostream>
#include <sstream>

#include "Buildings/Building.h"
#include "CommandCenter.h"
#include "Commands/AllCommand.h"
#include "Commands/AssetsCommand.h"
#include "Commands/BankruptCommand.h"
#include "Commands/CommandContext.h"
#include "Commands/ImproveCommand.h"
#include "Commands/MortgageCommand.h"
#include "Commands/NextCommand.h"
#include "Commands/RollCommand.h"
#include "Commands/SaveCommand.h"
#include "Commands/TradeCommand.h"
#include "Commands/UnmortgageCommand.h"
#include "Player.h"

CommandCenter::CommandCenter(bool testing)
    : context{std::make_shared<CommandContext>()} {
  context->board = std::make_shared<Board>(context->players);
  context->testing = testing;

  commands.emplace(RollCommand::NAME, std::make_unique<RollCommand>(context));
  commands.emplace(NextCommand::NAME, std::make_unique<NextCommand>(context));
  commands.emplace(TradeCommand::NAME, std::make_unique<TradeCommand>(context));
  commands.emplace(ImproveCommand::NAME,
                   std::make_unique<ImproveCommand>(context));
  commands.emplace(MortgageCommand::NAME,
                   std::make_unique<MortgageCommand>(context));
  commands.emplace(UnmortgageCommand::NAME,
                   std::make_unique<UnmortgageCommand>(context));
  commands.emplace(BankruptCommand::NAME,
                   std::make_unique<BankruptCommand>(context));
  commands.emplace(AssetsCommand::NAME,
                   std::make_unique<AssetsCommand>(context));
  commands.emplace(AllCommand::NAME, std::make_unique<AllCommand>(context));
  commands.emplace(SaveCommand::NAME, std::make_unique<SaveCommand>(context));
}

void CommandCenter::addPlayer(const std::string &name, char piece, int funds) {
  context->players.emplace_back(std::make_shared<Player>(name, piece, funds));
  context->board->getBuildings()[0]->addPlayer(context->players.back());
  if (!context->cur_player) {
    context->cur_player = context->players[0];
    context->cur_player_idx = 0;
  }
}

void CommandCenter::loadPlayer(const std::string &name, char piece, int funds,
                               int position, int tims_cups, int jail_turns) {
  context->players.emplace_back(std::make_shared<Player>(name, piece, funds));
  auto &player = context->players.back();
  player->setPosition(position);
  for (int n = 0; n < tims_cups; n++) {
    player->addCup();
  }
  if (jail_turns != -1) {
    player->setTurnsInTims(jail_turns + 1);
  }
  context->board->getBuildings()[position]->addPlayer(player);
  if (!context->cur_player) {
    context->cur_player = player;
    context->cur_player_idx = 0;
  }
}

void CommandCenter::loadProperty(const std::string &name,
                                 const std::string &owner, int improvements) {
  if (owner == "BANK") {
    return;
  }
  for (auto &building : context->board->getBuildings()) {
    if (building->getName() == name) {
      if (auto property =
              std::dynamic_pointer_cast<OwnableBuilding>(building)) {
        for (auto &player : context->players) {
          if (player->getName() == owner) {
            player->addProperty(property);
            property->setOwner(player);
            if (improvements == -1) {
              property->toggleMortgaged();
            } else if (improvements > 0) {
              if (auto academic_building =
                      std::dynamic_pointer_cast<AcademicBuilding>(property)) {
                for (int n = 0; n < improvements; n++) {
                  academic_building->improve();
                }
              } else {
                throw("ERROR: Saved property is marked with improvements but "
                      "is not an academic building.");
              }
            }
            return;
          }
        }
        throw("ERROR: Saved property owner does not exist.");
      } else {
        throw("ERROR: Saved property is non-ownable.");
      }
    }
  }
}

void CommandCenter::displayPlayers() const {
  std::cout << "Players:\n";
  std::cout << "--------\n";
  for (size_t i = 0; i < context->players.size(); i++) {
    auto &player = context->players[i];
    if (player->isActive()) {
      std::cout << "- " << player->getName() << " (" << player->getPiece()
                << ")\n";
    }
  }
}

bool CommandCenter::scan() {
  std::string input;

  std::cout << "> ";
  std::getline(std::cin, input);

  if (input.empty()) {
    return false;
  }

  std::istringstream iss{input};
  params.clear();
  if (iss >> command && !(commands.contains(command))) {
    std::cout << "command not found: " << input << "\n";
    return false;
  }
  std::string param;
  while (iss >> param) {
    params.push_back(param);
  }
  return true;
}

bool CommandCenter::execute() {
  // TODO: lookup command in command hashmap, then execute
  if (!context->cur_player) {
    return false;
  }
  commands[command]->execute(params);

  int num_active = 0;
  for (auto &player : context->players) {
    if (player->isActive()) {
      num_active++;
    }
    if (num_active > 1) {
      return true;
    }
  }
  return false;
}
