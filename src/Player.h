#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>

class OwnableBuilding;

class Player {
public:
  Player(const std::string &name, char piece, int funds);

  std::string getName() const;

  char getPiece() const;

  int getBalance() const;

  void increaseFunds(int amount);

  void reduceFunds(int amount);

  void setPosition(int n);

  int getPosition() const;

  const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> &
  getProperties() const;

  void addProperty(std::shared_ptr<OwnableBuilding> property);

private:
  std::string name;
  char piece;
  int balance;
  int position;
  std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> properties;
  int num_residences;
};

#endif