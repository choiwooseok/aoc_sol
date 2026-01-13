#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../util.h"

int getPriorities(char ch) {
  if ('a' <= ch && ch <= 'z') {
    return ch - '0' - 48;
  } else {
    return ch - '0' + 10;
  }
}

int part1(const std::vector<std::string>& lines) {
  int ret = 0;
  for (auto& line : lines) {
    std::string elem0 = line.substr(0, line.length() / 2);
    std::string elem1 = line.substr(line.length() / 2);

    for (char ch : elem0) {
      if (std::find(elem1.begin(), elem1.end(), ch) != elem1.end()) {
        ret += getPriorities(ch);
        break;
      }
    }
  }

  return ret;
}

int part2(const std::vector<std::string>& lines) {
  int ret = 0;
  for (int i = 0; i < lines.size(); i += 3) {
    for (char ch : lines[i]) {
      if (std::find(lines[i + 1].begin(), lines[i + 1].end(), ch) != lines[i + 1].end()) {
        if (std::find(lines[i + 2].begin(), lines[i + 2].end(), ch) != lines[i + 2].end()) {
          ret += getPriorities(ch);
          break;
        }
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day3/input.txt");

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