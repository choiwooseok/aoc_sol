#include <iostream>
#include <unordered_map>
#include "../util.h"

int part1(const std::vector<std::string>& lines) {
  int two = 0;
  int three = 0;
  for (const auto& line : lines) {
    std::unordered_map<char, int> m;
    for (auto& ch : line) {
      m[ch]++;
    }
    bool hasTwo = false;
    bool hasThree = false;
    for (auto& [k, v] : m) {
      if (hasTwo && hasThree) break;
      if (v == 2) {
        hasTwo = true;
      }
      if (v == 3) {
        hasThree = true;
      }
    }
    if (hasTwo) two++;
    if (hasThree) three++;
  }
  return two * three;
}

std::string part2(const std::vector<std::string>& lines) {
  for (const auto& line1 : lines) {
    for (const auto& line2 : lines) {
      if (line1 == line2) continue;

      int cnt = 0;
      std::string ret = "";
      for (int i = 0; i < line1.size(); i++) {
        if (line1[i] == line2[i]) {
          ret += line1[i];
        } else {
          cnt++;
        }
      }

      if (cnt == 1) return ret;
    }
  }
  return "";
}

int main(int argc, char** argv) {
  auto lines = read_lines("day2/input.txt");

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
