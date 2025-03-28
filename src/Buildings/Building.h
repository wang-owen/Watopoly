#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <unordered_set>

class Building {
public:
  Building(const std::string &name);

  virtual ~Building() = default;

  std::string getName() const;

  void addPiece(char c);

  void removePiece(char c);

  std::unordered_set<char>& getVisitingPieces();

private:
  std::string name;
  std::unordered_set<char> visiting_pieces;
};

#endif