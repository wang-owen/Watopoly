#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "Command.h"

class Board;

class SaveCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string SaveCommand::NAME = "save";

#endif