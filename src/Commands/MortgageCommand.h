#ifndef MORTGAGECOMMAND_H
#define MORTGAGECOMMAND_H

#include "Command.h"

class Board;

class MortgageCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string MortgageCommand::NAME = "mortgage";

#endif