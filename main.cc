#include <format>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Board.h"
#include "PieceManager.h"
#include "Player.h"

void formatError(std::string &message) {
  std::cerr << std::format("ERROR: {}\n", message);
}

int main(int argc, char *argv[]) {
  // Verify arguments
  if (argc > 2) {
    std::cerr << std::format("Usage: {} [-test]\n", argv[0]);
    return 1;
  }

  // Create board
  Board board{};

  // Prompt for player count
  int numPlayers = 0;
  std::cout << std::format("Enter number of players ({}-{}): ",
                           Board::MIN_PLAYERS, Board::MAX_PLAYERS);
  while (!(std::cin >> numPlayers) || numPlayers < Board::MIN_PLAYERS ||
         numPlayers > Board::MAX_PLAYERS) {
    std::cout << std::format(
        "Invalid input. Please enter an integer between {} and {}: ",
        Board::MIN_PLAYERS, Board::MAX_PLAYERS);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Prompt for player name and piece choice
  PieceManager pm{};
  for (auto n = 1; n <= numPlayers; n++) {
    std::cout << std::endl;
    pm.displayPieces();

    std::string username, input, extra;
    int pieceNum;

    while (true) {
      std::cout << std::format(
          "\nEnter your username (alphanumeric, one word) and piece (1-{}): ",
          pm.getNumPieces());
      std::getline(std::cin, input);

      std::istringstream iss(input);
      if (!(iss >> username >> pieceNum) || username.empty() ||
          !std::all_of(username.begin(), username.end(), ::isalnum) ||
          pieceNum < 1 || pieceNum > pm.getNumPieces() ||
          !(pm.isAvailable(pieceNum)) || (iss >> extra)) {
        std::cout << "Invalid input. Try again.\n";
      } else {
        break;
      }
    }

    // Initialize player
    auto player = std::make_unique<Player>(username, pm.selectPiece(pieceNum));
    board.addPlayer(std::move(player));
  }

  // Display all players
  std::cout << std::endl;
  board.displayPlayers();

  // Gameplay loop

  return 0;
}