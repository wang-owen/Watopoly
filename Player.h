#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "Piece.h"

class Building;

class Player {
public:
  Player(const std::string &username, const Piece &piece, int funds);

  Player(std::string &&username, Piece &&piece, int funds);

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