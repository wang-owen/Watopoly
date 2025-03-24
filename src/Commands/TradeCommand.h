#ifndef TRADECOMMAND_H
#define TRADECOMMAND_H

#include "Command.h"

class Board;

class TradeCommand : public Command {
public:
  static const std::string NAME;

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params = {}) override {}
};

const std::string TradeCommand::NAME = "trade";

#endif