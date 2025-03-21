#include "Player.h"

Player::Player(std::string username, Piece piece)
    : username{username}, piece{piece} {}

std::string Player::getUsername() const { return username; }

Piece Player::getPiece() const { return piece; }