#include <iostream>
#include <random>

#include "../util.h"

std::vector<int> _parse(const std::string &line) {
  std::vector<std::string> tokens = split(line, ",");
  std::vector<int> ret;
  for (auto &token : tokens) {
    if (!token.empty())
      ret.push_back(stoi(token));
  }
  return ret;
}

void program(std::vector<int> &inputs) {
  for (int i = 0, n = inputs.size(); i < n; i++) {
    if (i % 4 == 0) {
      int op_code = inputs[i];
      int var1 = n > inputs[i + 1] ? inputs[inputs[i + 1]] : std::numeric_limits<int>::min();
      int var2 = n > inputs[i + 2] ? inputs[inputs[i + 2]] : std::numeric_limits<int>::min();
      int idx = n > inputs[i + 3] ? inputs[i + 3] : std::numeric_limits<int>::min();

      if (idx != std::numeric_limits<int>::min()) {
        switch (op_code) {
          case 1:  // ADD
            inputs[idx] = var1 + var2;
            break;
          case 2:  // MUL
            inputs[idx] = var1 * var2;
            break;
          case 99:  // FIN
          default:
            break;
        }
      }
    }
  }
}

int part1(const std::string &line) {
  auto input = _parse(line);
  input[1] = 12;
  input[2] = 2;
  program(input);

  return input[0];
}

int part2(const std::string &line) {
  std::vector<int> origin = _parse(line);
  std::vector<int> inputs = origin;

  std::random_device rd;   // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 99);

  while (inputs[0] != 19690720) {
    inputs[1] = distrib(gen);  // noun
    inputs[2] = distrib(gen);  // verb
    program(inputs);
    if (inputs[0] == 19690720) {
      return 100 * inputs[1] + inputs[2];
    }
    inputs = origin;
  }

  return -1;
}

int main(int argc, char **argv) {
  auto line = read_line("day2/input.txt");

  {
    auto [result, ms] = measure_ms(part1, line);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, line);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}