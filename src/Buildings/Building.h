#ifndef BUILDING_H
#define BUILDING_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Player;
class Board;

class Building {
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

#endif
