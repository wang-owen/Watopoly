#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

class Building;

class Board {
public:
  Board();

  void displayBoard() const;

  const std::vector<std::shared_ptr<Building>> &getBuildings() const;

private:
  std::vector<std::shared_ptr<Building>> buildings;
};

#endif