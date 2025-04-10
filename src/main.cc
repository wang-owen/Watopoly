#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_set>

#include "CommandCenter.h"
#include "PieceManager.h"

std::string initNewGame(CommandCenter &cmd) {
  const int STARTING_FUNDS = 1500;
  const int MIN_PLAYERS = 2;
  const int MAX_PLAYERS = 6;

  // Prompt for player count
  int numPlayers = 0;
  std::cout << "\nEnter number of players (" << MIN_PLAYERS << "-"
            << MAX_PLAYERS << "): ";
  while (!(std::cin >> numPlayers) || numPlayers < MIN_PLAYERS ||
         numPlayers > MAX_PLAYERS) {
    std::cout << "Invalid input. Please enter an integer between "
              << MIN_PLAYERS << " and " << MAX_PLAYERS << ": ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Setup player objects
  std::string first_player;
  PieceManager pm{};
  std::unordered_set<std::string> taken_names;
  for (auto n = 1; n <= numPlayers; n++) {
    std::cout << "\n";
    pm.displayPieces();

    std::string name, input, extra;
    int pieceNum;

    // Prompt for name and piece type
    while (true) {
      // Prompt for name
      std::cout << "\nPlayer " << n << " - Enter name (alpha, one word): ";
      std::getline(std::cin, input);

      std::istringstream iss(input);
      if (!(iss >> name) || name.empty() ||
          !std::all_of(name.begin(), name.end(), ::isalpha) || (iss >> extra)) {
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
      int num_pieces = pm.getNumPieces();
      std::cout << name << " - Enter piece selection (1-" << num_pieces
                << "): ";
      while (!(std::cin >> pieceNum) || pieceNum < 1 || pieceNum > num_pieces ||
             !pm.isAvailable(pieceNum)) {
        if (!pm.isAvailable(pieceNum)) {
          std::cout << "Piece already taken. Try again: ";
        } else {
          std::cout << "Invalid input. Please enter an integer between 1 and "
                    << num_pieces << ": ";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }

    // Initialize player
    taken_names.insert(name);
    cmd.addPlayer(name, pm.selectPiece(pieceNum), STARTING_FUNDS);
    if (first_player.empty()) {
      first_player = name;
    }
  }
  return first_player;
}

std::string loadSavedGame(CommandCenter &cmd, const std::string &filename) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "ERROR: Could not open file " << filename << std::endl;
    return "";
  }

  // Read number of players.
  std::string first_player;
  int numPlayers = 0;
  infile >> numPlayers;
  infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Load each player.
  for (int i = 0; i < numPlayers; ++i) {
    std::string name;
    char piece;
    int tims_cups;
    int money;
    int position;

    infile >> name >> piece >> tims_cups >> money >> position;

    int jail_indicator = 0;
    int jail_turns = -1;
    // If the player is in DC Tims Line there is an extra field
    if (position == 10) {
      infile >> jail_indicator;
      if (jail_indicator == 1) {
        infile >> jail_turns;
      }
    }
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cmd.loadPlayer(name, piece, money, position, tims_cups, jail_turns);
    if (first_player.empty()) {
      first_player = name;
    }
  }

  // Load property information
  std::string property_name;
  while (infile >> property_name) {
    std::string owner;
    int improvements;
    infile >> owner >> improvements;
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cmd.loadProperty(property_name, owner, improvements);
  }

  return first_player;
}

int main(int argc, char *argv[]) {
  // Verify arguments
  if (argc > 4) {
    std::cerr << "Usage: " << argv[0] << " [-load file] [-testing]\n";
    return 1;
  }

  bool testing = false;
  std::string load_file;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-testing") {
      testing = true;
    } else if (arg == "-load") {
      if (i + 1 < argc) {
        load_file = argv[++i];
      } else {
        std::cerr << "Error: Missing filename after -load.\n";
        std::cerr << "Usage: " << argv[0] << " [-load file] [-testing]\n";
        return 1;
      }
    } else {
      std::cerr << "Error: Unrecognized argument '" << arg << "'.\n";
      std::cerr << "Usage: " << argv[0] << " [-load file] [-testing]\n";
      return 1;
    }
  }

  // Initialize command center
  CommandCenter cmd{testing};

  std::string first_player;
  if (load_file.empty()) {
    first_player = initNewGame(cmd);
  } else {
    first_player = loadSavedGame(cmd, load_file);
    if (first_player.empty()) {
      return 1;
    }
  }

  cmd.displayBoard();

  // Display players
  std::cout << "\n\n";
  cmd.displayPlayers();

  std::cout << "\n" << first_player << "'s turn:\n--------------\n";

  // Gameplay loop
  bool running = true;
  while (running) {
    if (!cmd.scan()) {
      continue;
    }
    running = cmd.execute();
    std::cout << "\n";
  }

  std::cout << "\n==========\nGAME OVER!\n==========" << std::endl;

  return 0;
}
