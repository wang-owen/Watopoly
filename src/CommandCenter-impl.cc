#include <format>
#include <iostream>
#include <sstream>

#include "CommandCenter.h"
#include "Commands/AllCommand.h"
#include "Commands/AssetsCommand.h"
#include "Commands/BankruptCommand.h"
#include "Commands/ImproveCommand.h"
#include "Commands/MortgageCommand.h"
#include "Commands/NextCommand.h"
#include "Commands/RollCommand.h"
#include "Commands/SaveCommand.h"
#include "Commands/TradeCommand.h"
#include "Commands/UnmortgageCommand.h"
#include "Player.h"

CommandCenter::CommandCenter() : board{std::make_unique<Board>()} {
  commands.emplace(RollCommand::NAME, std::make_unique<RollCommand>(board));
  commands.emplace(NextCommand::NAME, std::make_unique<NextCommand>());
  commands.emplace(TradeCommand::NAME, std::make_unique<TradeCommand>());
  commands.emplace(ImproveCommand::NAME, std::make_unique<ImproveCommand>());
  commands.emplace(MortgageCommand::NAME, std::make_unique<MortgageCommand>());
  commands.emplace(UnmortgageCommand::NAME,
                   std::make_unique<UnmortgageCommand>());
  commands.emplace(BankruptCommand::NAME, std::make_unique<BankruptCommand>());
  commands.emplace(AssetsCommand::NAME, std::make_unique<AssetsCommand>());
  commands.emplace(AllCommand::NAME, std::make_unique<AllCommand>());
  commands.emplace(SaveCommand::NAME, std::make_unique<SaveCommand>());
}

void CommandCenter::addPlayer(const std::string &name, char piece, int funds) {
  players.emplace_back(std::make_shared<Player>(name, piece, funds));
}

void CommandCenter::displayPlayers() const {
  std::cout << "Players:\n";
  std::cout << "--------\n";
  for (size_t i = 0; i < players.size(); i++) {
    std::cout << std::format("Player {}: {} ({})\n", static_cast<int>(i + 1),
                             players[i]->getName(), players[i]->getPiece());
  }
}

bool CommandCenter::parse(const std::string &input) {
  // TODO: verify command validity, return false if invalid
  if (input.empty()) {
    return false;
  }

  std::istringstream iss{input};
  params.clear();
  if (iss >> command && !(commands.contains(command))) {
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
  return commands[command]->execute(cur_player, params);
}