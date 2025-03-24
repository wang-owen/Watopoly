#include "Buildings/Building.h"
#include "Player.h"

Player::Player(const std::string &name, char piece, int balance)
    : name{name}, piece{piece}, balance{balance}, position{0} {}

std::string Player::getName() const { return name; }

char Player::getPiece() const { return piece; }

int Player::getBalance() const { return balance; }

void Player::increaseFunds(int amount) { balance += amount; }

void Player::reduceFunds(int amount) {
  balance = (balance - amount >= 0) ? balance - amount : 0;
}

void Player::setPosition(int n) { position = n; }

int Player::getPosition() const { return position; }

const std::unordered_map<std::string, std::shared_ptr<Building>> &
Player::getProperties() const {
  return properties;
}