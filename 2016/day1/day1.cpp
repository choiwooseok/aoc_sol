#include <iostream>
#include <format>
#include <set>
#include "../util.h"

enum class DIRECTION {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

using Point = std::pair<int, int>;

void update_dir(char turn, DIRECTION& dir) {
  if (turn == 'R') {
    dir = static_cast<DIRECTION>((static_cast<int>(dir) + 1) % 4);
  } else {
    dir = static_cast<DIRECTION>((static_cast<int>(dir) + 3) % 4);
  }
}

void update_pos(DIRECTION dir, int step, int& x, int& y) {
  switch (dir) {
    case DIRECTION::NORTH:
      y += step;
      break;
    case DIRECTION::EAST:
      x += step;
      break;
    case DIRECTION::SOUTH:
      y -= step;
      break;
    case DIRECTION::WEST:
      x -= step;
      break;
  }
}

int part1(const std::string& line) {
  auto instructions = split(line, ", ");
  int x = 0, y = 0;
  DIRECTION dir = DIRECTION::NORTH;

  for (auto& inst : instructions) {
    char turn = inst.at(0);
    int step = std::stoi(inst.substr(1));
    update_dir(turn, dir);
    update_pos(dir, step, x, y);
  }

  return std::abs(x) + std::abs(y);
}

int part2(const std::string& line) {
  auto instructions = split(line, ", ");
  int x = 0, y = 0;
  DIRECTION dir = DIRECTION::NORTH;

  std::set<Point> visited;
  visited.insert({x, y});

  for (auto& inst : instructions) {
    char turn = inst.at(0);
    int step = std::stoi(inst.substr(1));
    update_dir(turn, dir);

    for (int i = 0; i < step; ++i) {
      update_pos(dir, 1, x, y);
      if (visited.count({x, y})) return std::abs(x) + std::abs(y);
      visited.insert({x, y});
    }
  }

  return 0;
}

int main(int argc, char** argv) {
  auto line = read_line("day1/input.txt");

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