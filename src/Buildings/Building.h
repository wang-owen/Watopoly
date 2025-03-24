#ifndef BUILDING_H
#define BUILDING_H

#include <memory>
#include <string>
#include <unordered_set>

class Player;

class Building {
public:
  Building() = default;

  void addPiece(char c);

  void removePiece(char c);

private:
  std::unordered_set<char> visiting_pieces;
};

#endif