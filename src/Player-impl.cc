#include "Buildings/OwnableBuilding.h"
#include "Buildings/ResidenceBuilding.h"
#include "Player.h"

Player::Player(const std::string &name, char piece, int balance)
    : name{name}, piece{piece}, balance{balance}, debt{0}, position{0},
      num_residences{0} {}

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

void Player::setPosition(int n) { position = n; }

int Player::getPosition() const { return position; }

std::vector<std::shared_ptr<OwnableBuilding>> Player::getProperties() const {
  std::vector<std::shared_ptr<OwnableBuilding>> vals;
  vals.reserve(properties.size());
  for (auto kv : properties) {
    vals.push_back(kv.second);
  }
  return vals;
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