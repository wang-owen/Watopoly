#include "Building.h"
#include "Player.h"

Player::Player(std::string username, Piece piece, int funds)
    : username{username}, piece{piece}, funds{funds} {}

std::string Player::getUsername() const { return username; }

Piece Player::getPiece() const { return piece; }

int Player::getFunds() const { return funds; }