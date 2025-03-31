export module CommandContext;

import <memory>;
import <vector>;
import Board;
import Player;

export struct CommandContext {
  bool testing;
  std::shared_ptr<Board> board;
  std::vector<std::shared_ptr<Player>> players;
  std::shared_ptr<Player> cur_player;
  int cur_player_idx;
  std::shared_ptr<int> active_cups;
};

