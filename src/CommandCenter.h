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
  CommandCenter(bool testing = false);

  void addPlayer(const std::string &name, char piece, int funds);

  void loadPlayer(const std::string &name, char piece, int funds, int position,
                  int tims_cups, int jail_turns);

  void loadProperty(const std::string &name, const std::string &owner,
                    int improvements);

  void displayPlayers() const;

  bool scan();

  bool execute();

private:
  std::unordered_map<std::string, std::unique_ptr<Command>> commands;
  std::string command;
  std::vector<std::string> params;
  std::shared_ptr<CommandContext> context;
};

#endif
