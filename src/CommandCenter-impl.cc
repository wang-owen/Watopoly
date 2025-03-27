#include <format>
#include <iostream>
#include <sstream>

#include "CommandCenter.h"
#include "Commands/CommandContext.h"
#include "Commands/NextCommand.h"
#include "Commands/RollCommand.h"
#include "Player.h"
// #include "Commands/AllCommand.h"
#include "Commands/AssetsCommand.h"
#include "Commands/BankruptCommand.h"
// #include "Commands/ImproveCommand.h"
// #include "Commands/MortgageCommand.h"
// #include "Commands/SaveCommand.h"
// #include "Commands/TradeCommand.h"
// #include "Commands/UnmortgageCommand.h"

CommandCenter::CommandCenter() : context{std::make_shared<CommandContext>()} {
  context->board = std::make_shared<Board>();

  commands.emplace(RollCommand::NAME, std::make_unique<RollCommand>(context));
  commands.emplace(NextCommand::NAME, std::make_unique<NextCommand>(context));
  // commands.emplace(TradeCommand::NAME,
  // std::make_unique<TradeCommand>(context));
  // commands.emplace(ImproveCommand::NAME,
  //                  std::make_unique<ImproveCommand>(context));
  // commands.emplace(MortgageCommand::NAME,
  //                  std::make_unique<MortgageCommand>(context));
  // commands.emplace(UnmortgageCommand::NAME,
  //                  std::make_unique<UnmortgageCommand>(context));
  commands.emplace(BankruptCommand::NAME,
                   std::make_unique<BankruptCommand>(context));
  commands.emplace(AssetsCommand::NAME, std::make_unique<AssetsCommand>(context));
  // commands.emplace(AllCommand::NAME, std::make_unique<AllCommand>(context));
  // commands.emplace(SaveCommand::NAME,
  // std::make_unique<SaveCommand>(context));
}

void CommandCenter::addPlayer(const std::string &name, char piece, int funds) {
  context->players.emplace_back(std::make_shared<Player>(name, piece, funds));
  if (!context->cur_player) {
    context->cur_player = context->players[0];
    context->cur_player_idx = 0;
  }
}

void CommandCenter::displayPlayers() const {
  std::cout << "Players:\n";
  std::cout << "--------\n";
  for (size_t i = 0; i < context->players.size(); i++) {
    auto &player = context->players[i];
    if (player->isActive()) {
      std::cout << std::format("Player {}: {} ({})\n", static_cast<int>(i + 1),
                               player->getName(), player->getPiece());
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
    std::cout << std::format("command not found: {}\n", input);
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
  bool running = commands[command]->execute();
  return running;
}
