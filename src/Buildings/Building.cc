export module Building;

import <memory>;
import <string>;
import <unordered_map>;
import <vector>;

import Board;
import Player;

export class Building {
public:
  Building(const std::string &name);

  virtual ~Building() = default;

  std::string getName() const;

  void addPlayer(const std::shared_ptr<Player> player);

  void removePiece(char piece);

  std::vector<char> getVisitingPieces() const;

  std::vector<std::shared_ptr<Player>> getVisitors() const;

  virtual void processEvent(const std::shared_ptr<Player> player) = 0;

private:
  std::string name;
  std::unordered_map<char, std::shared_ptr<Player>> visitors;
};

