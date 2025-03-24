#ifndef ASSETSCOMMAND_H
#define ASSETSCOMMAND_H

#include "Command.h"

class Board;

class AssetsCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string AssetsCommand::NAME = "assets";

#endif