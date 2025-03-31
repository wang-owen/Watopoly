#ifndef DICE_H
#define DICE_H

#include <random>
#include <vector>

class Dice {
public:
  Dice() = delete;

  static std::vector<int> roll(int sides, int n);

  static bool getProbability(double p);

  static int getDiscreteProbability(const std::vector<double> &probabilities);

private:
  static std::mt19937 gen;
};

#endif
