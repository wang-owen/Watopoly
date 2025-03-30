#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/Building.h"
#include "../Player.h"
#include "CommandContext.h"
#include "TradeCommand.h"

const std::string TradeCommand::NAME = "trade";

TradeCommand::TradeCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void TradeCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 3) {
    std::cout << "Usage: trade <name> <give> <receive>\n";
    return;
  }

  auto &player = context->cur_player;
  if (params[0] == player->getName()) {
    std::cout << "You cannot start a trade with yourself!\n";
    return;
  }

  std::shared_ptr<Player> recipient = nullptr;
  // Check if recipient exists
  for (auto &p : context->players) {
    if (p->getName() == params[0]) {
      recipient = p;
    }
  }
  if (!recipient) {
    std::cout << "Recipient does not exist!\n";
    return;
  }

  std::string give = params[1];
  std::string receive = params[2];
  bool give_is_num = std::all_of(give.begin(), give.end(), ::isdigit);
  bool receive_is_num = std::all_of(receive.begin(), receive.end(), ::isdigit);

  int give_amt, receive_amt;
  if (give_is_num && receive_is_num) {
    std::cout << "You cannot trade money for money!\n";
    return;
  } else if (give_is_num) {
    std::istringstream iss{give};
    iss >> give_amt;
    if (player->getBalance() < give_amt) {
      std::cout << "You lack sufficient funds for this trade!\n";
      return;
    }
  } else if (receive_is_num) {
    std::istringstream iss{receive};
    iss >> receive_amt;
  }

  std::shared_ptr<OwnableBuilding> give_property = nullptr;
  if (!give_is_num) {
    auto &properties = player->getProperties();
    std::cerr << receive << '\n';
    for (auto &property : properties) {
      std::cout << property.first << "\n";
    }
    if (!properties.count(receive)) {
      std::cout << std::format("You do not own {}!\n", give);
      return;
    }

    give_property = properties.at(give);
    if (auto academic =
            std::dynamic_pointer_cast<AcademicBuilding>(give_property)) {
      if (playerMonopolyHasImprovements(properties, academic->getBlock())) {
        std::cout << "You cannot trade properties that have improvements "
                     "in its monopoly!\n";
        return;
      }
    }
  }

  std::shared_ptr<OwnableBuilding> receive_property = nullptr;
  if (!receive_is_num) {
    auto &properties = recipient->getProperties();
    if (!properties.count(receive)) {
      std::cout << std::format("You do not own {}!\n", give);
      return;
    }

    receive_property = properties.at(receive);
    if (auto academic =
            std::dynamic_pointer_cast<AcademicBuilding>(receive_property)) {
      if (playerMonopolyHasImprovements(properties, academic->getBlock())) {
        std::cout << "You cannot trade properties that have improvements "
                     "in its monopoly!\n";
        return;
      }
    }
  }

  while (true) {
    std::cout << std::format("{}: {} is offering to give you {} in "
                             "exchange for {}. Accept? (y/n) ",
                             recipient->getName(), player->getName(),
                             give_is_num ? "$" + give : give,
                             receive_is_num ? "$" + receive : receive);
    std::string input, extra;
    char answer;
    std::getline(std::cin, input);
    std::istringstream iss{input};

    if (!(iss >> answer) || (iss >> extra)) {
      std::cout << "Invalid input. Try again.\n";
      continue;
    }

    switch (std::tolower(answer)) {
    case 'y': {
      if (!give_is_num && !receive_is_num) {
        give_property->setOwner(recipient);
        recipient->addProperty(give_property);
        receive_property->setOwner(player);
        player->addProperty(receive_property);
      } else if (give_is_num) {
        player->reduceFunds(give_amt);
        recipient->increaseFunds(give_amt);
        receive_property->setOwner(player);
        player->addProperty(receive_property);
      } else {
        if (recipient->getBalance() < receive_amt) {
          std::cout << std::format(
              "{} lacks sufficient funds for this trade!\n",
              recipient->getName());
          return;
        }
        recipient->reduceFunds(receive_amt);
        player->increaseFunds(receive_amt);
        give_property->setOwner(recipient);
        recipient->addProperty(give_property);
      }
      std::cout << "Trade accepted!\n";
      return;
    }
    case 'n': {
      std::cout << "Trade offer declined.\n";
      return;
    }
    default:
      continue;
    }
  }
}

bool TradeCommand::playerMonopolyHasImprovements(
    const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>>
        &properties,
    MonopolyBlock block) const {
  for (auto &name : AcademicBuilding::getBlockBuildings(block)) {
    if (!properties.contains(name)) {
      break;
    }
    if (std::dynamic_pointer_cast<AcademicBuilding>(properties.at(name))
            ->getNumImprovements() > 0) {
      return true;
    }
  }
  return false;
}