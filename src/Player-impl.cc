#include "Buildings/Building.h"
#include "Player.h"

Player::Player(const std::string &name, char piece, int funds)
    : name{name}, piece{piece}, funds{funds}, position{0} {}

std::string Player::getName() const { return name; }

char Player::getPiece() const { return piece; }

int Player::getFunds() const { return funds; }

void Player::setPosition(int n) { position = n; }

int Player::getPosition() const { return position; }

const std::unordered_map<std::string, std::shared_ptr<Building>> &
Player::getProperties() const {
  return properties;
}