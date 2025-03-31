export module Board;

import <memory>;
import <vector>;
import Building;
import AcademicBuilding;
import Player;

export class Board {
public:
  Board(const std::vector<std::shared_ptr<Player>> &players,
        std::shared_ptr<int> active_cups);

  constexpr static const int MAX_CUPS = 4;

  void displayBoard() const;

  std::string
  printImprovements(std::shared_ptr<AcademicBuilding> building) const;

  std::string
  printEmptySquareWithPieces(std::shared_ptr<Building> building) const;

  const std::vector<std::shared_ptr<Building>> &getBuildings() const;

private:
  std::vector<std::shared_ptr<Building>> buildings;
};
