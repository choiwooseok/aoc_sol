#include <iostream>
#include <format>
#include <cmath>
#include <numeric>
#include <sstream>
#include <ranges>

#include "../util.h"

using Matrix = std::vector<std::vector<std::string>>;

Matrix _transpose(const Matrix& mat) {
  int r = mat.size();
  int c = mat.front().size();
  Matrix ret(c, std::vector<std::string>(r, ""));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      ret[j][i] = mat[i][j];
    }
  }
  return ret;
}

Matrix _parse_col(const std::vector<std::string>& lines) {
  Matrix mat;
  for (auto& line : lines) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string elem;
    while (ss >> elem) row.push_back(elem);
    mat.push_back(row);
  }

  return _transpose(mat);
}

void _remove_space(std::string& str) {
  while (str.ends_with(' ')) str.pop_back();
  while (str.starts_with(' ')) str = str.substr(1);
}

Matrix _parse_rtl(const std::vector<std::string>& lines) {
  Matrix mat;

  std::vector<std::string> cols(lines.front().size());
  for (int j = 0; j < lines.front().size(); j++) {
    for (int i = 0; i < lines.size(); i++) {
      cols[j] += lines[i][j];
    }
  }
  std::reverse(cols.begin(), cols.end());

  std::vector<std::string> row;
  for (auto& col : cols) {
    std::string op = "";
    if (col.ends_with('*')) op = "*";
    if (col.ends_with('+')) op = "+";
    if (!op.empty()) col.pop_back();

    _remove_space(col);

    if (!col.empty()) {
      row.push_back(col);
    }

    if (!op.empty()) {
      row.push_back(op);
      mat.push_back(row);
      row.clear();
    }
  }

  return mat;
}

auto _calc = [](const Matrix& mat) -> uint64_t {
  return mat |
         std::views::transform([](const auto& col) {
           char op = col.back()[0];
           auto values = col | std::views::take(col.size() - 1);

           if (op == '*') {
             return std::accumulate(values.begin(), values.end(), 1ULL,
                                    [](uint64_t acc, const std::string& s) {
                                      return acc * std::stoull(s);
                                    });
           } else {  // op == '+'
             return std::accumulate(values.begin(), values.end(), 0ULL,
                                    [](uint64_t acc, const std::string& s) {
                                      return acc + std::stoull(s);
                                    });
           }
         }) |
         [](auto rng) {
           return std::accumulate(rng.begin(), rng.end(), 0ULL);
         };
};

uint64_t part1(const std::vector<std::string>& lines) {
  return lines |
         _parse_col |
         _calc;
}

uint64_t part2(const std::vector<std::string>& lines) {
  return lines |
         _parse_rtl |
         _calc;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day6/input.txt");

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
