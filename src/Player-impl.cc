#include <format>
#include <iostream>

#include "Buildings/OwnableBuilding.h"
#include "Buildings/ResidenceBuilding.h"
#include "Player.h"

Player::Player(const std::string &name, char piece, int balance)
    : name{name}, piece{piece}, balance{balance}, debt{0}, position{0},
      num_residences{0}, num_cups{0}, turns_in_tims{0}, active{true},
      rolled{false} {}

void Player::deactivate() { active = false; }

bool Player::isActive() const { return active; }

bool Player::hasRolled() const { return rolled; }

void Player::toggleRolled() { rolled = !rolled; }

std::string Player::getName() const { return name; }

char Player::getPiece() const { return piece; }

int Player::getBalance() const { return balance; }

int Player::getDebt() const { return debt; }

void Player::setDebt(int amount) { debt = amount; }

void Player::increaseFunds(int amount) { balance += amount; }

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

  position = new_pos;
  buildings[position]->removePlayer(shared_from_this());
  buildings[new_pos]->addPlayer(shared_from_this());

  std::cout << std::format("Moved {} steps to {}\n", steps,
                           buildings[new_pos]->getName());

  // Take action on building landed upon
  auto &building = buildings[new_pos];
  building->processEvent(shared_from_this());
}

void Player::moveToIdx(
    int i, const std::vector<std::shared_ptr<Building>> &buildings) {
  position = i;
  buildings[position]->removePlayer(shared_from_this());
  buildings[i]->addPlayer(shared_from_this());

  std::cout << std::format("Moved to {}\n", buildings[i]->getName());

  // Take action on building landed upon
  auto &building = buildings[i];
  building->processEvent(shared_from_this());
}

int Player::getCups() const { return num_cups; }

void Player::addCup() { num_cups++; }

void Player::removeCup() { num_cups = num_cups - 1 < 0 ? 0 : num_cups - 1; }

int Player::getTurnsInTims() const { return turns_in_tims; }

void Player::setTurnsInTims(int turns) { turns_in_tims = turns; }

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

void Player::addProperty(std::shared_ptr<OwnableBuilding> property) {
  properties[property->getName()] = property;
  if (std::dynamic_pointer_cast<ResidenceBuilding>(property)) {
    num_residences++;
  }
}
