#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include <unordered_set>
#include <vector>

enum class PieceType {
  Goose,
  GRTBus,
  TimHortonsDoughnut,
  Professor,
  Student,
  Money,
  Laptop,
  PinkTie
};

class PieceManager {
public:
  PieceManager();

  void displayPieces();

  int getNumPieces() const;

  bool isAvailable(int idx) const;

  char selectPiece(int idx);

private:
  static const std::vector<std::pair<char, std::string>> PIECES;
  static const std::vector<PieceType> PIECE_TYPES;
  std::unordered_set<PieceType> available_pieces;
};

#endif