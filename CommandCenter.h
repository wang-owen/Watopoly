#include <memory>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Player.h"

class CommandCenter {
public:
  CommandCenter();

  void addPlayer(std::string username, Piece piece, int funds);

  void displayPlayers();

private:
  std::unique_ptr<Board> board;
  std::vector<std::shared_ptr<Player>> players;
};