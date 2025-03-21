#include <utility>

#include "Board.h"

void Board::displayBoard() const {}

void Board::addPlayer(std::unique_ptr<Player> player) {
  players.emplace_back(std::move(player));
}

void Board::displayPlayers() const {
  for (auto &p : players) {
    auto piece = p->getPiece();
    std::cout << std::format("{} - ({}, {})\n", p->getUsername(), piece.name,
                             piece.symbol);
  }
}