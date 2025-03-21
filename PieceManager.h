#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include <string>
#include <unordered_set>
#include <vector>

#include "Piece.h"

class PieceManager {
public:
  PieceManager();

  void displayPieces();

  int getNumPieces() const;

  bool isAvailable(int idx) const;

  Piece selectPiece(int idx);

private:
  Piece createPiece(PieceType type);

  std::vector<PieceType> pieces;
  std::unordered_set<PieceType> available_pieces;
};

#endif