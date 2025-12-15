#include <iostream>
#include <format>
#include <queue>
#include <map>
#include <ranges>

#include "../util.h"

using Grid = std::vector<std::vector<char>>;
using Point = std::pair<int, int>;

auto _grid = [](const std::vector<std::string>& lines) -> Grid {
  return lines |
         std::views::transform([](const std::string& line) {
           return std::vector<char>(line.begin(), line.end());
         }) |
         [](auto rng) { return Grid(rng.begin(), rng.end()); };
};

auto _find_start = [](const Grid& grid) -> Point {
  int rows = grid.size();
  int cols = grid[0].size();

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == 'S') return {r, c};
    }
  }
  return {-1, -1};
};

bool isSafe(int y, int x, int r, int c) {
  return y >= 0 && y < r && x >= 0 && x < c;
}

auto count_obstacles_bfs = [](const Grid& grid, Point start) {
  int r = grid.size();
  int c = grid.front().size();
  std::vector<std::vector<bool>> visited(r, std::vector<bool>(c, false));

  uint64_t cnt = 0;

  std::queue<Point> q;
  q.push(start);

  while (!q.empty()) {
    auto [cy, cx] = q.front();
    q.pop();

    if (isSafe(cy, cx, r, c) && visited[cy][cx] == false) {
      visited[cy][cx] = true;

      if (grid[cy][cx] == '^') {
        cnt++;
        q.push({cy, cx - 1});
        q.push({cy, cx + 1});
      } else {
        q.push({cy + 1, cx});
      }
    }
  }
  return cnt;
};

int part1(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  auto start = _find_start(grid);
  return count_obstacles_bfs(grid, start);
}

auto count_paths_dp = [](const Grid& grid, Point start) -> uint64_t {
  int rows = grid.size();
  int cols = grid[0].size();
  std::vector<std::vector<uint64_t>> dp(rows, std::vector<uint64_t>(cols, 0));

  for (int c = 0; c < cols; ++c) dp[rows - 1][c] = 1;

  for (int r = rows - 2; r >= 0; --r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '^') {
        if (c > 0) dp[r][c] += dp[r + 1][c - 1];
        if (c < cols - 1) dp[r][c] += dp[r + 1][c + 1];
      } else {
        dp[r][c] = dp[r + 1][c];
      }
    }
  }
  return dp[start.first][start.second];
};

uint64_t part2(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  auto start = _find_start(grid);
  return count_paths_dp(grid, start);
}

int main(int argc, char** argv) {
  auto lines = read_lines("day7/input.txt");

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
