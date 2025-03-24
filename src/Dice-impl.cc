#include <cstdlib>
#include <ctime>

#include "Dice.h"

Dice::Dice(int numSides) : numSides{numSides} {}

void Dice::setSides(int n) { numSides = n; }

std::vector<int> Dice::roll(int n) const {
  std::vector<int> rolls;
  std::srand(std::time({}));
  for (int i = 0; i < n; i++) {
    rolls.push_back((std::rand() % numSides) + 1);
  }
  return rolls;
}