#include <iostream>
#include <format>
#include <queue>
#include <map>

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

bool isSafe(int y, int x, int r, int c) {
  return y >= 0 && y < r && x >= 0 && x < c;
}

void _part1(std::vector<std::vector<char>>& grid, const std::pair<int, int>& start, int& cnt) {
  int r = grid.size();
  int c = grid.front().size();
  std::vector<std::vector<bool>> visited(r, std::vector<bool>(c, false));

  std::queue<std::pair<int, int>> q;
  q.push(start);

  while (!q.empty()) {
    auto [cy, cx] = q.front();
    q.pop();

    if (isSafe(cy, cx, r, c) && visited[cy][cx] == false) {
      visited[cy][cx] = true;
      if (grid[cy][cx] == '.') {
        grid[cy][cx] = '|';
      }

      if (grid[cy][cx] == '^') {
        cnt++;
        q.push({cy, cx - 1});
        q.push({cy, cx + 1});
      } else {
        q.push({cy + 1, cx});
      }
    }
  }
}

int part1(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  int r = grid.size();
  int c = grid.front().size();

  int cnt = 0;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] == 'S') {
        _part1(grid, {i, j}, cnt);
        break;
      }
    }
  }

  return cnt;
}

uint64_t part2(const std::vector<std::string>& lines) {
  auto grid = _grid(lines);
  int r = grid.size();
  int c = grid.front().size();

  std::vector<std::vector<uint64_t>> dp(r, std::vector<uint64_t>(c, 0ULL));
  for (int i = 0; i < c; i++) {
    dp[r - 1][i] = 1ULL;
  }

  for (int i = r - 2; i >= 0; i--) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] == '^') {
        dp[i][j] = 0ULL;

        // left
        if (j - 1 >= 0) {
          dp[i][j] += dp[i + 1][j - 1];
        }

        // right
        if (j + 1 < c) {
          dp[i][j] += dp[i + 1][j + 1];
        }
      } else {
        dp[i][j] = dp[i + 1][j];
      }
    }
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] == 'S') {
        return dp[i][j];
      }
    }
  }

  return 0;
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
