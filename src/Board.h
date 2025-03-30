#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

class Building;
class AcademicBuilding;

class Board {
public:
  Board();

  constexpr static const int MAX_CUPS = 4;

  void displayBoard() const;

  std::string
  printImprovements(std::shared_ptr<AcademicBuilding> building) const;

  std::string
  printEmptySquareWithPieces(std::shared_ptr<Building> building) const;

  const std::vector<std::shared_ptr<Building>> &getBuildings() const;

private:
  std::vector<std::shared_ptr<Building>> buildings;
  std::shared_ptr<int> active_cups;
};

#endif