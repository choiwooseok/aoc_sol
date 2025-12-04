#include <iostream>
#include <array>
#include <limits>
#include <format>

#include "../util.h"

static std::string substringBefore(const std::string& str, const std::string& separator) {
  if (str.empty() || separator.empty()) {
    return str;
  }
  return str.find(separator) == std::string::npos ? str : str.substr(0, str.find(separator));
}

static std::string substringAfter(const std::string& str, const std::string& separator) {
  if (str.empty()) {
    return str;
  }
  if (separator.empty()) {
    return "";
  }
  return str.find(separator) == std::string::npos ? "" : str.substr(str.find(separator) + separator.length());
}

std::vector<std::array<int, 4>> _parse(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::array<int, 4>> data;

  std::string x1y1;
  std::string arrow;
  std::string x2y2;
  while (!inputs.eof()) {
    inputs >> x1y1 >> arrow >> x2y2;
    int x1 = std::stoi(substringBefore(x1y1, ","));
    int y1 = std::stoi(substringAfter(x1y1, ","));
    int x2 = std::stoi(substringBefore(x2y2, ","));
    int y2 = std::stoi(substringAfter(x2y2, ","));
    data.push_back({x1, y1, x2, y2});
  }
  inputs.close();
  return data;
}

int countOverlap(std::vector<std::vector<int>>& diagram) {
  int cnt = 0;
  for (auto row : diagram) {
    for (int col : row) {
      if (col > 1) {
        cnt++;
      }
    }
  }
  return cnt;
}

int part1(std::vector<std::array<int, 4>>& data) {
  int w = std::numeric_limits<int>::min();
  int h = std::numeric_limits<int>::min();
  for (auto line : data) {
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];
    w = std::max(x2, std::max(w, x1));
    h = std::max(y2, std::max(h, y1));
  }

  std::vector<std::vector<int>> diagram(h + 1, std::vector<int>(w + 1, 0));
  for (auto line : data) {
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];

    if (x1 == x2) {
      int y = x1;
      int x = (y1 < y2) ? y1 : y2;
      int x_fin = (y1 < y2) ? y2 : y1;
      for (; x <= x_fin; x++) {
        diagram[x][y]++;
      }
    } else if (y1 == y2) {
      int x = y1;
      int y = (x1 < x2) ? x1 : x2;
      int y_fin = (x1 < x2) ? x2 : x1;
      for (; y <= y_fin; y++) {
        diagram[x][y]++;
      }
    }
  }

  return countOverlap(diagram);
}

int part2(std::vector<std::array<int, 4>>& data) {
  int w = std::numeric_limits<int>::min();
  int h = std::numeric_limits<int>::min();
  for (auto line : data) {
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];
    w = std::max(x2, std::max(w, x1));
    h = std::max(y2, std::max(h, y1));
  }

  std::vector<std::vector<int>> diagram(h + 1, std::vector<int>(w + 1, 0));
  for (auto line : data) {
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];

    // horizontal && vertical
    if (x1 == x2) {
      int y = x1;
      int x = (y1 < y2) ? y1 : y2;
      int x_fin = (y1 < y2) ? y2 : y1;
      for (; x <= x_fin; x++) {
        diagram[x][y]++;
      }
    } else if (y1 == y2) {
      int x = y1;
      int y = (x1 < x2) ? x1 : x2;
      int y_fin = (x1 < x2) ? x2 : x1;
      for (; y <= y_fin; y++) {
        diagram[x][y]++;
      }
    }

    // digonal
    if (x1 != x2 && y1 != y2) {
      int x = y1;
      int y = x1;

      int x_fin = y2;
      int y_fin = x2;

      if (x < x_fin && y < y_fin) {
        for (; x <= x_fin; x++) {
          diagram[x][y]++;
          y++;
        }
      } else if (x < x_fin && y > y_fin) {
        for (; x <= x_fin; x++) {
          diagram[x][y]++;
          y--;
        }
      } else if (x > x_fin && y < y_fin) {
        for (; x >= x_fin; x--) {
          diagram[x][y]++;
          y++;
        }
      } else if (x > x_fin && y > y_fin) {
        for (; x >= x_fin; x--) {
          diagram[x][y]++;
          y--;
        }
      }
    }
  }

  return countOverlap(diagram);
}

int main(int argc, char** argv) {
  std::vector<std::array<int, 4>> data = _parse("day5/input.txt");

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