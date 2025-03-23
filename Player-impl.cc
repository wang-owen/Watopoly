#include "Building.h"
#include "Player.h"

Player::Player(const std::string &username, const Piece &piece, int funds)
    : username{username}, piece{piece}, funds{funds} {}

Player::Player(std::string &&username, Piece &&piece, int funds)
    : username{std::move(username)}, piece{std::move(piece)}, funds{funds} {}

std::string Player::getUsername() const { return username; }

Piece Player::getPiece() const { return piece; }

int Player::getFunds() const { return funds; }