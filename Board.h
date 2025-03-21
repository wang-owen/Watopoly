#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>
#include <vector>

#include "Player.h"

class Board {
public:
  void displayBoard() const;

  void addPlayer(std::unique_ptr<Player> player);

  void displayPlayers() const;

  static const int MIN_PLAYERS = 2;
  static const int MAX_PLAYERS = 6;

private:
  std::vector<std::unique_ptr<Player>> players;
};

#endif