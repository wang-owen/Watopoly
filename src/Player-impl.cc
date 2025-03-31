#include <iostream>

#include "Buildings/OwnableBuilding.h"
#include "Buildings/ResidenceBuilding.h"
#include "Player.h"

Player::Player(const std::string &name, char piece, int balance)
    : name{name}, piece{piece}, balance{balance}, debt{0}, position{0},
      num_residences{0}, num_cups{0}, turns_in_tims{0}, doubles_rolled{0},
      active{true}, rolled{false}, can_roll_again{false} {}

void Player::deactivate() { active = false; }

bool Player::isActive() const { return active; }

bool Player::hasRolled() const { return rolled; }

void Player::setRolled(bool b) { rolled = b; }

bool Player::canRollAgain() const { return can_roll_again; }

void Player::setCanRollAgain(bool b) { can_roll_again = b; }

std::string Player::getName() const { return name; }

char Player::getPiece() const { return piece; }

int Player::getPosition() const { return position; }

void Player::setPosition(int pos) { position = pos; }

int Player::getBalance() const { return balance; }

void Player::displayBalance() const {
  std::cout << "Balance: $" << balance << "\n";
}

int Player::getDebt() const { return debt; }

void Player::setDebt(int amount) { debt = amount; }

void Player::increaseFunds(int amount) {
  if (debt > 0) {
    if (amount <= debt) {
      debt -= amount;
      std::cout << "You have paid off $" << amount
                << " of your debt. You have $" << debt
                << " of debt remaining.\n";
      return;
    } else {
      amount -= debt;
      debt = 0;
      std::cout << "You have paid off your debt!\n";
    }
  }
  balance += amount;
}

int Player::reduceFunds(int amount) {
  // Returns the amount reduced
  if (balance - amount < 0) {
    auto reduced = balance;
    balance = 0;
    return reduced;
  }
  balance -= amount;
  return amount;
}

void Player::move(int steps,
                  const std::vector<std::shared_ptr<Building>> &buildings) {
  auto ptr = shared_from_this();

  auto buildings_size = static_cast<int>(buildings.size());

  int new_pos;
  if (steps >= 0) {
    new_pos = (position + steps < buildings_size)
                  ? position + steps
                  : position + steps - buildings_size;
  } else {
    new_pos = (position + steps > 0) ? position + steps
                                     : buildings_size + position + steps;
  }

  buildings[position]->removePiece(piece);

  // Check if player has passed Collect OSAP
  if (new_pos > 0 && position + steps >= buildings_size) {
    buildings[0]->processEvent(ptr);
  }

  buildings[new_pos]->addPlayer(ptr);
  position = new_pos;

  std::cout << "Moved " << steps << " steps to "
            << buildings[position]->getName() << "\n";

  // Take action on building landed upon
  auto &building = buildings[position];
  building->processEvent(ptr);
}

void Player::moveToIdx(
    int i, const std::vector<std::shared_ptr<Building>> &buildings) {
  buildings[position]->removePiece(piece);
  buildings[i]->addPlayer(shared_from_this());
  position = i;

  std::cout << "Moved to " << buildings[i]->getName() << "\n";

  // Take action on building landed upon
  auto &building = buildings[i];
  building->processEvent(shared_from_this());
}

int Player::getCups() const { return num_cups; }

void Player::addCup() { num_cups++; }

void Player::removeCup() { num_cups = num_cups - 1 < 0 ? 0 : num_cups - 1; }

int Player::getTurnsInTims() const { return turns_in_tims; }

void Player::setTurnsInTims(int turns) { turns_in_tims = turns; }

int Player::getDoublesRolled() const { return doubles_rolled; }

void Player::setDoublesRolled(int n) { doubles_rolled = n; }

const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> &
Player::getProperties() const {
  return properties;
}

std::shared_ptr<OwnableBuilding>
Player::getProperty(const std::string &name) const {
  auto it = properties.find(name);
  if (it != properties.end()) {
    return it->second;
  }
  return nullptr;
}

void Player::addProperty(const std::shared_ptr<OwnableBuilding> &property) {
  properties[property->getName()] = property;
  if (std::dynamic_pointer_cast<ResidenceBuilding>(property)) {
    num_residences++;
  }
}

void Player::removeProperty(const std::shared_ptr<OwnableBuilding> &property) {
  properties.erase(property->getName());
}

void Player::displayAssets() const {
  std::cout << name << "'s assets:\n----------------\n";
  std::cout << "Cash: $" << balance << "\n";
  std::cout << "Roll Up the Rim cups: " << num_cups << "\n";
  std::cout << "Properties:\n";
  for (auto &property : properties) {
    std::cout << "- " << property.first << "\n";
  }
  std::cout << "\n";
}
