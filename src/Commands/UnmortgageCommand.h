#ifndef UNMORTGAGECOMMAND_H
#define UNMORTGAGECOMMAND_H

#include "Command.h"

class Board;

class UnmortgageCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string UnmortgageCommand::NAME = "unmortgage";

#endif