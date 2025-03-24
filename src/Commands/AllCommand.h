#ifndef ALLCOMMAND_H
#define ALLCOMMAND_H

#include "Command.h"

class Board;

class AllCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string AllCommand::NAME = "all";

#endif