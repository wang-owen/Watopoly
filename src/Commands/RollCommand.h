#ifndef ROLLCOMMAND_H
#define ROLLCOMMAND_H

#include "Command.h"

class Board;

class RollCommand : public Command {
public:
  static const std::string NAME;

  explicit RollCommand(std::weak_ptr<Board> board);

  bool execute(std::shared_ptr<Player> player,
               const std::vector<std::string> &params) override;

private:
  std::weak_ptr<Board> board;
};

#endif