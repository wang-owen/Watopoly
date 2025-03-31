export module Dice;

import <random>;
import <vector>;

export class Dice {
public:
  Dice() = delete;

  static std::vector<int> roll(int sides, int n);

  static bool getProbability(double p);

  static int getDiscreteProbability(const std::vector<double> &probabilities);

private:
  static std::mt19937 gen;
};

