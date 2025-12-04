#include <iostream>
#include <format>
#include "../util.h"

std::vector<std::vector<char>> _grid(const std::vector<std::string>& lines) {
  int r = lines.size();
  int c = lines.front().size();
  std::vector<std::vector<char>> grid(r, std::vector<char>(c, '.'));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      grid[i][j] = lines[i][j];
    }
  }
  return grid;
}

std::vector<std::pair<int, int>> directions = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};

int part1(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  int r = grid.size();
  int c = grid.front().size();

  int ret = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '@') continue;
      int cnt = 0;
      for (auto& [dx, dy] : directions) {
        int nx = i + dx;
        int ny = j + dy;
        if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
        if (grid[nx][ny] == '@') cnt++;
      }
      if (cnt < 4) ret++;
    }
  }

  return ret;
}

int part2(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  int r = grid.size();
  int c = grid.front().size();

  int removed = 0;
  bool canRemove = true;

  while (canRemove) {
    canRemove = false;

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (grid[i][j] != '@') continue;
        int cnt = 0;
        for (auto& [dx, dy] : directions) {
          int nx = i + dx;
          int ny = j + dy;
          if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
          if (grid[nx][ny] == '@') cnt++;
        }
        if (cnt < 4) {
          grid[i][j] = '.';
          removed++;
          canRemove = true;
        }
      }
    }
  }

  return removed;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day4/input.txt");

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
