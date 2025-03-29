#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>

#include "CommandCenter.h"
#include "PieceManager.h"

int main(int argc, char *argv[]) {
  // Verify arguments
  if (argc > 3) {
    std::cerr << std::format("Usage: {} [-load file] [-testing] \n", argv[0]);
    return 1;
  }

  // Initialize command center
  CommandCenter cmd{};

  const int STARTING_FUNDS = 1500;
  const int MIN_PLAYERS = 2;
  const int MAX_PLAYERS = 6;

  // Prompt for player count
  int numPlayers = 0;
  std::cout << std::format("Enter number of players ({}-{}): ", MIN_PLAYERS,
                           MAX_PLAYERS);
  while (!(std::cin >> numPlayers) || numPlayers < MIN_PLAYERS ||
         numPlayers > MAX_PLAYERS) {
    std::cout << std::format(
        "Invalid input. Please enter an integer between {} and {}: ",
        MIN_PLAYERS, MAX_PLAYERS);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Setup player objects
  PieceManager pm{};
  std::unordered_set<std::string> taken_names;
  for (auto n = 1; n <= numPlayers; n++) {
    std::cout << std::endl;
    pm.displayPieces();

    std::string name, input, extra;
    int pieceNum;

    // Prompt for name and piece type
    while (true) {
      // Prompt for name
      std::cout << std::format(
          "\nPlayer {} - Enter name (alphanumeric, one word): ", n);
      std::getline(std::cin, input);

      std::istringstream iss(input);
      if (!(iss >> name) || name.empty() ||
          !std::all_of(name.begin(), name.end(), ::isalnum) || (iss >> extra)) {
        std::cout << "Invalid input. Try again.\n";
        continue;
      } else if (taken_names.contains(name)) {
        std::cout << "Name taken. Try again.\n";
        continue;
      } else if (name == "BANK") {
        std::cout << "You cannot choose 'BANK' as a name. Try again.\n";
        continue;
      }      

      // Prompt for piece type
      int numPieces = pm.getNumPieces();
      std::cout << std::format("Player {} - Enter piece selection (1-{}): ", n,
                               numPieces);
      while (!(std::cin >> pieceNum) || pieceNum < 1 || pieceNum > numPieces ||
             !pm.isAvailable(pieceNum)) {
        std::cout << std::format(
            "Invalid input. Please enter an integer between 1 and {}: ",
            numPieces);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }

    // Initialize player
    taken_names.insert(name);
    cmd.addPlayer(name, pm.selectPiece(pieceNum), STARTING_FUNDS);
  }

  // Display players
  std::cout << "\n\n";
  cmd.displayPlayers();
  std::cout << "\n";

  std::cout << std::format("\nPlayer 1 turn:\n--------------\n");

  // Gameplay loop
  bool running = true;
  while (running) {
    if (!cmd.scan()) {
      continue;
    }
    running = cmd.execute();
    std::cout << std::endl;
  }

  std::cout << "\n==========\nGAME OVER!\n==========" << std::endl;

  return 0;
}