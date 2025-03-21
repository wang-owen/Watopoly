#include <iostream>
#include <stdexcept>

#include "PieceManager.h"

PieceManager::PieceManager()
    : pieces{PieceType::Goose,
             PieceType::GRTBus,
             PieceType::TimHortonsDoughnut,
             PieceType::Professor,
             PieceType::Student,
             PieceType::Money,
             PieceType::Laptop,
             PieceType::PinkTie},
      available_pieces{pieces.begin(), pieces.end()} {}

void PieceManager::displayPieces() {
  std::cout << "Available pieces:\n";
  std::cout << "-----------------\n";
  for (size_t i = 1; i <= pieces.size(); i++) {
    auto pc = createPiece(pieces[i - 1]);
    std::cout << std::format("{} - {} ({})\n",
                             (isAvailable(i) ? std::to_string(i) : "X"),
                             pc.name, pc.symbol);
  }
}

int PieceManager::getNumPieces() const {
  return static_cast<int>(pieces.size());
}

bool PieceManager::isAvailable(int n) const {
  return available_pieces.contains(pieces.at(n - 1));
}

Piece PieceManager::selectPiece(int n) {
  if (isAvailable(n)) {
    available_pieces.erase(pieces[n - 1]);
    return createPiece(pieces[n - 1]);
  }
  throw std::runtime_error("Piece not available!");
}

Piece PieceManager::createPiece(PieceType type) {
  switch (type) {
  case PieceType::Goose:
    return {"Goose", 'G'};
  case PieceType::GRTBus:
    return {"GRT Bus", 'B'};
  case PieceType::TimHortonsDoughnut:
    return {"Tim Hortons Doughnut", 'D'};
  case PieceType::Professor:
    return {"Professor", 'P'};
  case PieceType::Student:
    return {"Student", 'S'};
  case PieceType::Money:
    return {"Money", '$'};
  case PieceType::Laptop:
    return {"Laptop", 'L'};
  case PieceType::PinkTie:
    return {"Pink Tie", 'T'};
  default:
    throw std::invalid_argument("Invalid piece type");
  }
}