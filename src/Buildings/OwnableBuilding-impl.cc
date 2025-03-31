#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>

#include "../Player.h"
#include "OwnableBuilding.h"

OwnableBuilding::OwnableBuilding(
    const std::string &name, int cost,
    const std::vector<std::shared_ptr<Player>> &players)
    : Building{name}, cost{cost}, has_owner{false}, mortgaged{false},
      players{players} {}

int OwnableBuilding::getCost() const { return cost; }

bool OwnableBuilding::hasOwner() const { return has_owner; }

void OwnableBuilding::setOwner(const std::shared_ptr<Player> player) {
  owner = player;
  has_owner = player ? true : false;
}

std::shared_ptr<Player> OwnableBuilding::getOwner() const { return owner; }

void OwnableBuilding::toggleMortgaged() { mortgaged = !mortgaged; }

bool OwnableBuilding::isMortgaged() const { return mortgaged; }

void OwnableBuilding::auctionProperty(
    std::vector<std::shared_ptr<Player>> players,
    const std::shared_ptr<Player> player) {
  std::cout << getName() << " is being auctioned!\n-----------------------\n";

  if (player) {
    players.erase(std::remove(players.begin(), players.end(), player),
                  players.end());
  }

  int current_bid = 0;
  // Loop until only one bidder remains.
  do {
    for (size_t i = 0; i < players.size();) {
      const std::shared_ptr<Player> &p = players[i];
      bool valid_input = false;
      while (!valid_input) {
        std::cout << p->getName() << "'s turn:\n";
        std::cout << "1. Raise\n";
        std::cout << "2. Withdraw\n";
        std::cout << "Enter your choice: ";

        int choice;
        if (!(std::cin >> choice)) {
          std::cout << "Invalid input. Please enter 1 or 2.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          continue;
        }

        if (choice == 1) {
          std::cout << "Enter your bid amount (must be greater than "
                    << current_bid << "): ";
          int amount;
          if (!(std::cin >> amount)) {
            std::cout << "Invalid amount. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
          }
          if (amount <= current_bid) {
            std::cout << "Bid amount must be greater than the current bid ("
                      << current_bid << ").\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
          }
          if (p->getBalance() < amount) {
            std::cout << "Insufficient funds. Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
          }
          // Accept the bid and update current_bid.
          current_bid = amount;
          std::cout << p->getName() << " raised the bid to " << current_bid
                    << ".\n";
          valid_input = true;
        } else if (choice == 2) {
          std::cout << p->getName() << " has withdrawn.\n";
          // Remove the player from active bidders.
          players.erase(players.begin() + i);
          valid_input = true;
          // Don't increment i because the next player has shifted into the
          // current index.
          continue;
        } else {
          std::cout
              << "Invalid choice. Please enter 1 to raise or 2 to withdraw.\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      // Only increment the index if the current player did not withdraw.
      if (i < players.size() && players[i] == p) {
        ++i;
      }

      if (players.size() == 1) {
        break;
      }
    }
  } while (players.size() > 1);

  if (players.size() == 1) {
    std::cout << players.front()->getName() << " wins the bid with $"
              << current_bid << "!\n";

    if (has_owner) {
      owner->removeProperty(shared_from_this());
    }
    players.front()->reduceFunds(current_bid);
    players.front()->addProperty(shared_from_this());
  } else {
    std::cout << "Bidding round ended with no active bidders.\n";
  }
}

void OwnableBuilding::processEvent(const std::shared_ptr<Player> player) {
  if (!hasOwner()) {
    // Building is available for purchase
    auto property_cost = getCost();
    bool error = true;
    while (error) {
      std::cout << "Would you like to purchase " << getName() << " for $"
                << property_cost << "? (y/n) ";

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

        std::cout << "\n"
                  << player->getName() << " has purchased " << getName()
                  << " for $" << property_cost << "\n";
        error = false;
        break;
      }

      case 'n': {
        auctionProperty(players);
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
      std::cout << getName() << " Fee: $" << fee << "\n";
      auto reduced_funds = player->reduceFunds(fee);
      getOwner()->increaseFunds(reduced_funds);
      if (reduced_funds < fee) {
        // Player lacks sufficient funds
        player->setDebt(fee - reduced_funds, getOwner());
        std::cout << "You lack sufficient funds. You owe $"
                  << fee - reduced_funds << "\n";
      }
      player->displayBalance();
    }
  }
}
