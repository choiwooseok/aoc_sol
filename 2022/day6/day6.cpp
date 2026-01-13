#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "../util.h"

int part1(const std::string& data) {
  for (int i = 0; i < data.length() - 3; i++) {
    std::unordered_set<char> set;
    for (int j = 0; j < 4; j++) {
      set.insert(data[i + j]);
    }
    if (set.size() == 4) {
      return i + 4;
    }
  }
  return -1;
}

int part2(const std::string& data) {
  for (int i = 0; i < data.length() - 13; i++) {
    std::unordered_set<char> set;
    for (int j = 0; j < 14; j++) {
      set.insert(data[i + j]);
    }

    if (set.size() == 14) {
      return i + 14;
    }
  }
  return -1;
}

int main(int argc, char** argv) {
  auto data = read_line("day6/input.txt");

  {
    auto [result, ms] = measure_ms(part1, data);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, data);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}