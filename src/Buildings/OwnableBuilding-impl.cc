#include <format>
#include <iostream>
#include <sstream>

#include "../Player.h"
#include "OwnableBuilding.h"

OwnableBuilding::OwnableBuilding(const std::string &name, int cost)
    : Building{name}, cost{cost}, has_owner{false}, mortgaged{false} {}

int OwnableBuilding::getCost() const { return cost; }

bool OwnableBuilding::hasOwner() const { return has_owner; }

void OwnableBuilding::setOwner(const std::shared_ptr<Player> &player) {
  owner = player;
  has_owner = player ? true : false;
}

std::shared_ptr<Player> OwnableBuilding::getOwner() const {
  if (auto o = owner.lock()) {
    return o;
  }
  return nullptr;
}

void OwnableBuilding::toggleMortgaged() { mortgaged = !mortgaged; }

bool OwnableBuilding::isMortgaged() const { return mortgaged; }

void OwnableBuilding::processEvent(const std::shared_ptr<Player> &player) {
  if (!hasOwner()) {
    // Building is available for purchase
    auto property_cost = getCost();
    bool error = true;
    while (error) {
      std::cout << std::format("Would you like to purchase {} for ${}? (y/n) ",
                               getName(), property_cost);

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
        // Attempt to purchase property
        // Check player balance
        if (player->getBalance() < property_cost) {
          std::cout << "Insufficient funds.\n";
        } else {
          player->reduceFunds(property_cost);
          setOwner(player);
          player->addProperty(shared_from_this());
        }

        std::cout << std::format("\n{} has purchased {} for ${}\n",
                                 player->getName(), getName(), property_cost);
        error = false;
        break;
      }

      case 'n': {
        error = false;
        break;
      }

      default:
        continue;
      }
    }
    player->displayBalance();
  } else {
    // Pay fee
    if (!isMortgaged()) {
      auto fee = getFee();
      std::cout << std::format("{} Fee: ${}\n", getName(), fee);
      auto reduced_funds = player->reduceFunds(fee);
      getOwner()->increaseFunds(reduced_funds);
      if (reduced_funds < fee) {
        // Player lacks sufficient funds
        player->setDebt(fee - reduced_funds);
        std::cout << std::format("You lack sufficient funds. You owe ${}\n",
                                 fee - reduced_funds);
      }
      player->displayBalance();
    }
  }
}