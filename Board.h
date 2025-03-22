#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

class Building;

class Board {
public:
  void displayBoard() const;

private:
  std::vector<std::shared_ptr<Building>> buildings;
};

#endif