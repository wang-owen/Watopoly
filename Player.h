#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "Piece.h"

class Player {
public:
  Player(std::string username, Piece piece);

  std::string getUsername() const;

  Piece getPiece() const;

private:
  std::string username;
  Piece piece;
};

#endif