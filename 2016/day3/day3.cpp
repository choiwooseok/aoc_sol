#include <iostream>
#include <format>
#include <string>
#include <vector>
#include "../util.h"

std::vector<std::vector<int>> _parse(const std::vector<std::string>& lines) {
  std::vector<std::vector<int>> ret;
  for (auto& line : lines) {
    std::stringstream ss(line);
    int side;
    std::vector<int> sides;
    while (ss >> side) sides.push_back(side);
    ret.push_back(sides);
  }
  return ret;
}

bool isValidTriangle(int a, int b, int c) {
  return a + b > c && a + c > b && b + c > a;
}

int part1(const std::vector<std::string>& lines) {
  auto row = _parse(lines);
  int cnt = 0;
  for (auto& items : row) {
    if (isValidTriangle(items[0], items[1], items[2])) cnt++;
  }
  return cnt;
}

int part2(const std::vector<std::string>& lines) {
  auto row = _parse(lines);

  int cnt = 0;
  for (int i = 0; i < row.size(); i += 3) {
    for (int j = 0; j < 3; j++) {
      if (isValidTriangle(row[i][j], row[i + 1][j], row[i + 2][j])) cnt++;
    }
  }

  return cnt;
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