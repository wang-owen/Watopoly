#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class OwnableBuilding;

class Player {
public:
  Player(const std::string &name, char piece, int funds);

  void deactivate();

  bool isActive() const;

  bool hasRolled() const;

  void toggleRolled();

  std::string getName() const;

  char getPiece() const;

  int getBalance() const;

  int getDebt() const;

  void setDebt(int amount);

  void increaseFunds(int amount);

  int reduceFunds(int amount);

  void setPosition(int n);

  int getPosition() const;

  int getCups() const;

  void addCup();

  void removeCup();

  const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> &
  getProperties() const;

  std::shared_ptr<OwnableBuilding> getProperty(const std::string &name) const;

  void addProperty(std::shared_ptr<OwnableBuilding> property);

private:
  std::string name;
  char piece;
  int balance, debt, position, num_residences, num_cups;
  std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> properties;
  bool active, rolled;
};

#endif