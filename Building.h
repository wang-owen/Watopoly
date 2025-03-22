#ifndef BUILDING_H
#define BUILDING_H

#include <memory>
#include <string>
#include <vector>

class Player;

class Building {
public:
  Building();

  std::string getName();

private:
  std::string name;
  std::vector<std::weak_ptr<Player>>
      visitors; // change to hashset/map, decide how to hash each obj
};

#endif