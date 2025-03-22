#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "Building.h"
#include "Piece.h"

class Player {
public:
  Player(std::string username, Piece piece, int funds);

  std::string getUsername() const;

  Piece getPiece() const;

  int getFunds() const;

private:
  std::string username;
  Piece piece;
  int funds;
  std::weak_ptr<Building> location;
};

#endif