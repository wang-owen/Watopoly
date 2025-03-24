#ifndef IMPROVECOMMAND_H
#define IMPROVECOMMAND_H

#include "Command.h"

class Board;

class ImproveCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string ImproveCommand::NAME = "improve";

#endif