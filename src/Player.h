#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>

class Player {
public:
  Player(const std::string &name, char piece, int funds);

  std::string getName() const;

  char getPiece() const;

  int getFunds() const;

  void setPosition(int n);

  int getPosition() const;

  const std::unordered_map<std::string, std::shared_ptr<Building>> &
  getProperties() const;

private:
  std::string name;
  char piece;
  int funds;
  int position;
  std::unordered_map<std::string, std::shared_ptr<Building>> properties;
  int num_residences;
};

#endif