#include <iostream>
#include <format>
#include <cmath>
#include "../util.h"

int fuel(int mass) {
  return std::round(mass / 3) - 2;
}

long long part1(const std::vector<std::string>& lines) {
  long long sum = 0LL;
  for (auto& line : lines) {
    sum += fuel(std::stoi(line));
  }
  return sum;
}

long long part2(const std::vector<std::string>& lines) {
  long long sum = 0LL;
  for (auto& line : lines) {
    int temp = std::stoi(line);
    while (temp > 0) {
      int calc = fuel(temp);
      sum += calc < 0 ? 0 : calc;
      temp = calc;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day1/input.txt");

  {
    auto [result, ms] = measure_ms(part1, lines);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, lines);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}
