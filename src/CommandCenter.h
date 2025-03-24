#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Commands/Command.h"

struct CommandContext;

class Player;

class CommandCenter {
public:
  CommandCenter();

  void addPlayer(const std::string &name, char piece, int funds);

  void displayPlayers() const;

  bool parse(const std::string &input);

  bool execute();

private:
  std::unordered_map<std::string, std::unique_ptr<Command>> commands;
  std::string command;
  std::vector<std::string> params;
  std::shared_ptr<CommandContext> context;
};

#endif