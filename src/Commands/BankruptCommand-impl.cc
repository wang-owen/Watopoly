#include <format>
#include <iostream>
#include <sstream>

#include "../Buildings/OwnableBuilding.h"
#include "BankruptCommand.h"
#include "CommandContext.h"

const std::string BankruptCommand::NAME = "bankrupt";

BankruptCommand::BankruptCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void BankruptCommand::execute(const std::vector<std::string> & /*params*/) {
  auto &player = context->cur_player;

  if (player->getDebt() == 0) {
    std::cout << "You cannot declare bankruptcy with zero debt!\n";
    return;
  }

  auto &building = context->board->getBuildings()[player->getPosition()];
  if (auto b = std::dynamic_pointer_cast<OwnableBuilding>(building)) {
    // Player's assets go to building owner
    auto owner = b->getOwner();
    for (auto &[_, property] : player->getProperties()) {
      property->setOwner(owner);
      owner->addProperty(property);
      if (property->isMortgaged()) {
        int fee = property->getCost() * 0.1;
        std::cout << std::format(
            "{} must pay 10\% (${}) of the property cost!\n", owner->getName(),
            fee);
        int reduced_funds = owner->reduceFunds(fee);
        owner->displayBalance();
        if (reduced_funds < fee) {
          owner->setDebt(fee - reduced_funds);
          std::cout << std::format("You lack sufficient funds. You owe ${}\n",
                                   fee - reduced_funds);
        } else {
          int unmortgage_cost = property->getCost() * 0.5;
          while (true) {
            std::cout << std::format(
                "Would you like to unmortgage the property for ${}? (y/n) ",
                property->getCost() * 0.5);

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
              if (owner->getBalance() < unmortgage_cost) {
                std::cout << "Insufficient funds.\n";
                break;
              }
              owner->reduceFunds(unmortgage_cost);
              owner->displayBalance();
            }
            case 'n': {
              break;
            }
            default:
              continue;
            }
          }
        }
      }
    }
    // Transfer Roll Up the Rim tickets to owner
    for (int n = 0; n < player->getCups(); n++) {
      owner->addCup();
    }
  } else {
    // Player's assets go to bank
    for (auto &[_, property] : player->getProperties()) {
      if (property->isMortgaged()) {
        property->toggleMortgaged();
      }
      property->auctionProperty(player, context->players);
    }
  }

  player->deactivate();

  // Transfer control to next active player
  auto num_players = static_cast<int>(context->players.size());
  do {
    context->cur_player_idx = (context->cur_player_idx + 1 < num_players)
                                  ? context->cur_player_idx + 1
                                  : 0;
    player = context->players[context->cur_player_idx];
  } while (!player->isActive());

  context->board->displayBoard();

  std::cout << std::format("\n {}'s turn:\n--------------\n",
                           context->cur_player->getName());
}
