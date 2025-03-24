#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Board.h"
#include "Commands/Command.h"

class Player;

class CommandCenter {
public:
  CommandCenter();

  void addPlayer(const std::string &name, char piece, int funds);

  void displayPlayers() const;

  bool parse(const std::string &input);

  bool execute();

private:
  std::shared_ptr<Board> board;
  std::shared_ptr<Player> cur_player;
  std::vector<std::shared_ptr<Player>> players;
  std::string command;
  std::vector<std::string> params;
  std::unordered_map<std::string, std::unique_ptr<Command>> commands;
};

#endif