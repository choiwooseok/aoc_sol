#include <iostream>
#include <format>
#include <unordered_set>
#include "../util.h"

int part1(int start, const std::vector<std::string>& lines) {
  int ret = start;
  for (const auto& line : lines) {
    ret += stoi(line);
  }
  return ret;
}

int part2(int start, const std::vector<std::string>& lines) {
  std::unordered_set<int> seen{start};

  int ret = start;
  while (true) {
    for (const auto& line : lines) {
      ret += stoi(line);
      if (seen.count(ret)) {
        return ret;
      }
      seen.insert(ret);
    }
  }
  return -1;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day1/input.txt");

  {
    auto [result, ms] = measure_ms(part1, 0, lines);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, 0, lines);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}
