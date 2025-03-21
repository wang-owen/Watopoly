#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building {
public:
  Building();

  std::string getName();

private:
  std::string name;
};

#endif