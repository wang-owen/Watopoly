#include "Dice.h"

std::mt19937 Dice::gen(std::random_device{}());

std::vector<int> Dice::roll(int sides, int n) {
  static std::uniform_int_distribution<int> dist(1, sides);
  std::vector<int> rolls;
  for (int i = 0; i < n; i++) {
    rolls.push_back(dist(gen));
  }
  return rolls;
}

bool Dice::getProbability(double p) {
  static std::bernoulli_distribution dist(p);
  return dist(gen);
}

int Dice::getDiscreteProbability(const std::vector<double> &probabilities) {
  static std::discrete_distribution<int> dist(probabilities.begin(),
                                              probabilities.end());
  return dist(gen);
}
