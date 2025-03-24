#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>
#include <vector>

#include "../Player.h"

class Command {
public:
  virtual bool execute(std::shared_ptr<Player> player,
                       const std::vector<std::string> &params = {}) = 0;
};

#endif