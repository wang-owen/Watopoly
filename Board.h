#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

class Building;

class Board {
public:
  void displayBoard() const;

  static const int MIN_PLAYERS = 2;
  static const int MAX_PLAYERS = 6;

private:
  std::vector<std::shared_ptr<Building>> buildings;
};

#endif