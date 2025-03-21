#ifndef PIECE_H
#define PIECE_H

#include <string>

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

struct Piece {
  std::string name;
  char symbol;
};

#endif