#ifndef DICE_H
#define DICE_H

#include <vector>

class Dice {
public:
  Dice(int numSides);

  void setSides(int n);

  std::vector<int> roll(int n) const;

private:
  int numSides;
};

#endif
