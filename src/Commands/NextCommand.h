#ifndef NEXTCOMMAND_H
#define NEXTCOMMAND_H

#include "Command.h"

class Board;

class NextCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string NextCommand::NAME = "next";

#endif