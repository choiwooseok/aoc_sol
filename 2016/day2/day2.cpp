#include <iostream>
#include <format>
#include <string>
#include <vector>
#include "../util.h"

struct Point {
  int x, y;
};

enum class Direction { L,
                       R,
                       U,
                       D };

Direction charToDirection(char ch) {
  switch (ch) {
    case 'L':
      return Direction::L;
    case 'R':
      return Direction::R;
    case 'U':
      return Direction::U;
    case 'D':
      return Direction::D;
  }
  throw std::invalid_argument("invalid dir");
}

Point getNextPosition(const Point& p, Direction dir) {
  switch (dir) {
    case Direction::L:
      return {p.x - 1, p.y};
    case Direction::R:
      return {p.x + 1, p.y};
    case Direction::U:
      return {p.x, p.y - 1};
    case Direction::D:
      return {p.x, p.y + 1};
  }
  throw std::invalid_argument("invalid dir");
}

template <size_t Rows, size_t Cols>
bool isValidPosition(const std::vector<std::vector<std::string>>& keypad,
                     const Point& p) {
  return p.x >= 0 && p.x < Cols &&
         p.y >= 0 && p.y < Rows &&
         keypad[p.y][p.x] != " ";
}

std::string part1(const std::vector<std::string>& lines) {
  const std::vector<std::vector<std::string>> keypad = {
      {"1", "2", "3"},
      {"4", "5", "6"},
      {"7", "8", "9"}};

  Point pos = {1, 1};  // start at '5'
  std::string code;

  for (const auto& line : lines) {
    for (char ch : line) {
      Point next = getNextPosition(pos, charToDirection(ch));
      if (isValidPosition<3, 3>(keypad, next)) pos = next;
    }
    code += keypad[pos.y][pos.x];
  }

  return code;
}

std::string part2(const std::vector<std::string>& lines) {
  const std::vector<std::vector<std::string>> keypad = {
      {" ", " ", "1", " ", " "},
      {" ", "2", "3", "4", " "},
      {"5", "6", "7", "8", "9"},
      {" ", "A", "B", "C", " "},
      {" ", " ", "D", " ", " "}};

  Point pos = {0, 2};  // start at '5'
  std::string code;

  for (const auto& line : lines) {
    for (char ch : line) {
      Point next = getNextPosition(pos, charToDirection(ch));
      if (isValidPosition<5, 5>(keypad, next)) pos = next;
    }
    code += keypad[pos.y][pos.x];
  }

  return code;
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