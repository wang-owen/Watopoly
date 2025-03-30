#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Building;
class OwnableBuilding;

class Player : public std::enable_shared_from_this<Player> {
public:
  Player(const std::string &name, char piece, int funds);

  void deactivate();

  bool isActive() const;

  bool hasRolled() const;

  void setRolled(bool b);

  std::string getName() const;

  char getPiece() const;

  int getPosition() const;

  int getBalance() const;

  void displayBalance() const;

  int getDebt() const;

  void setDebt(int amount);

  void increaseFunds(int amount);

  int reduceFunds(int amount);

  void move(int steps, const std::vector<std::shared_ptr<Building>> &buildings);

  void moveToIdx(int i,
                 const std::vector<std::shared_ptr<Building>> &buildings);

  int getCups() const;

  void addCup();

  void removeCup();

  int getTurnsInTims() const;

  void setTurnsInTims(int turns);

  int getDoublesRolled() const;

  void setDoublesRolled(int n);

  bool canRollAgain() const;

  void setCanRollAgain(bool b);

  const std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> &
  getProperties() const;

  std::shared_ptr<OwnableBuilding> getProperty(const std::string &name) const;

  void addProperty(const std::shared_ptr<OwnableBuilding> &property);

  void removeProperty(const std::shared_ptr<OwnableBuilding> &property);

  void displayAssets() const;

private:
  std::string name;
  char piece;
  int balance, debt, position, num_residences, num_cups, turns_in_tims,
      doubles_rolled;
  std::unordered_map<std::string, std::shared_ptr<OwnableBuilding>> properties;
  bool active, rolled, can_roll_again;
};

#endif