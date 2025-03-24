#ifndef BANKRUPTCOMMAND_H
#define BANKRUPTCOMMAND_H

#include "Command.h"

class Board;

class BankruptCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string BankruptCommand::NAME = "bankrupt";

#endif