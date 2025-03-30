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

  auto &recipient = params[0];
  std::string give = params[1];
  std::string receive = params[2];
  bool give_is_num = std::all_of(give.begin(), give.end(), ::isdigit);
  bool receive_is_num = std::all_of(receive.begin(), receive.end(), ::isdigit);
  auto &players = context->players;

  if (give_is_num && receive_is_num) {
    std::cout << "You cannot trade money for money!\n";
    return;
  } else if (give_is_num) {
    int give_amt;
    std::istringstream iss{give};
    iss >> give_amt;

    if (player->getBalance() < give_amt) {
      std::cout << "You lack sufficient funds for this trade!\n";
      return;
    }

    for (auto &p : players) {
      auto name = p->getName();
      if (name == recipient) {
        auto &recipient_properties = p->getProperties();
        if (!recipient_properties.contains(receive)) {
          std::cout << std::format("{} does not own {}!\n", name, receive);
          return;
        }

        auto &property = recipient_properties.at(receive);
        if (auto academic =
                std::dynamic_pointer_cast<AcademicBuilding>(property)) {
          if (playerMonopolyHasImprovements(recipient_properties,
                                            academic->getBlock()))
            std::cout << "You cannot trade properties that have improvements "
                         "in its monopoly!\n";
        }

        while (true) {
          std::cout << std::format("{}: {} is offering to give you ${} in "
                                   "exchange for {}. Accept? (y/n) ",
                                   name, player->getName(), give_amt, receive);
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
            player->reduceFunds(give_amt);
            p->increaseFunds(give_amt);
            property->setOwner(player);
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
    }
    std::cout << "Recipient does not exist!\n";
  } else if (receive_is_num) {
    int receive_amt;
    std::istringstream iss{receive};
    iss >> receive_amt;

    for (auto &p : players) {
      auto name = p->getName();
      if (name == recipient) {
        auto &properties = player->getProperties();
        if (!properties.contains(receive)) {
          std::cout << std::format("You do not own {}!\n", give);
          return;
        }

        auto &property = properties.at(give);
        if (auto academic =
                std::dynamic_pointer_cast<AcademicBuilding>(property)) {
          if (playerMonopolyHasImprovements(properties, academic->getBlock()))
            std::cout << "You cannot trade properties that have improvements "
                         "in its monopoly!\n";
        }

        while (true) {
          std::cout << std::format("{}: {} is offering to give you {} in "
                                   "exchange for ${}. Accept? (y/n) ",
                                   name, player->getName(), give, receive_amt);
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
            player->increaseFunds(receive_amt);
            p->reduceFunds(receive_amt);
            property->setOwner(p);
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
    }
    std::cout << "Recipient does not exist!\n";
  } else {
    for (auto &p : players) {
      auto name = p->getName();
      if (name == recipient) {
        auto &player_properties = player->getProperties();
        if (!player_properties.contains(receive)) {
          std::cout << std::format("You do not own {}!\n", give);
          return;
        }

        auto &recipient_properties = p->getProperties();
        if (!recipient_properties.contains(receive)) {
          std::cout << std::format("{} does not own {}!\n", name, give);
          return;
        }

        auto &player_property = player_properties.at(give);
        if (auto academic =
                std::dynamic_pointer_cast<AcademicBuilding>(player_property)) {
          if (playerMonopolyHasImprovements(player_properties,
                                            academic->getBlock()))
            std::cout << "You cannot trade properties that have improvements "
                         "in its monopoly!\n";
        }

        auto &recipient_property = recipient_properties.at(receive);
        if (auto academic = std::dynamic_pointer_cast<AcademicBuilding>(
                recipient_property)) {
          if (playerMonopolyHasImprovements(recipient_properties,
                                            academic->getBlock()))
            std::cout << "You cannot trade properties that have improvements "
                         "in its monopoly!\n";
        }

        while (true) {
          std::cout << std::format("{}: {} is offering to give you {} in "
                                   "exchange for {}. Accept? (y/n) ",
                                   name, player->getName(), give, receive);
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
            player_property->setOwner(p);
            recipient_property->setOwner(player);
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
    }
    std::cout << "Recipient does not exist!\n";
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