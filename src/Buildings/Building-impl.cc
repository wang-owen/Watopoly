#include "../Board.h"
#include "../Player.h"
#include "Building.h"

Building::Building(const std::string &name) : name{name} {}

std::string Building::getName() const { return name; }

void Building::addPlayer(std::shared_ptr<Player> player) {
  visitors.insert(std::make_pair(player->getPiece(), player));
}

void Building::removePlayer(std::shared_ptr<Player> player) {
  visitors.erase(player->getPiece());
}

std::vector<char> Building::getVisitingPieces() const {
  std::vector<char> pieces;
  for (auto &[piece, _] : visitors) {
    pieces.push_back(piece);
  }
  return pieces;
}

std::vector<std::shared_ptr<Player>> Building::getVisitors() const {
  std::vector<std::shared_ptr<Player>> players;
  for (auto &[_, player] : visitors) {
    players.push_back(player);
  }
  return players;
}