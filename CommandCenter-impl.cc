#include <format>
#include <iostream>

#include "CommandCenter.h"

CommandCenter::CommandCenter() : board{std::make_unique<Board>()} {}

void CommandCenter::addPlayer(std::string username, Piece piece, int funds) {
  players.emplace_back(std::make_shared<Player>(username, piece, funds));
}

void CommandCenter::displayPlayers() {
  std::cout << "Players:\n";
  std::cout << "--------\n";
  for (size_t i = 0; i < players.size(); i++) {
    std::cout << std::format("Player {}: {} ({})\n", static_cast<int>(i + 1),
                             players[i]->getUsername(),
                             players[i]->getPiece().symbol);
  }
}