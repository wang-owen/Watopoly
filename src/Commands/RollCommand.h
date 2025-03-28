#ifndef ROLLCOMMAND_H
#define ROLLCOMMAND_H

#include "Command.h"

class RollCommand : public Command {
public:
  static const std::string NAME;

  explicit RollCommand(std::weak_ptr<CommandContext> context);

  bool execute(std::vector<std::string> params = {}) override;

private:
  bool ownableBuildingAction(std::shared_ptr<Player> player,
                             std::shared_ptr<OwnableBuilding> property);
};

#endif