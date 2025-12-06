#include <iostream>
#include <format>
#include <cmath>
#include <numeric>
#include <sstream>

#include "../util.h"

std::vector<std::vector<std::string>> _transpose(const std::vector<std::vector<std::string>>& arr) {
  int r = arr.size();
  int c = arr.front().size();
  std::vector<std::vector<std::string>> ret(c, std::vector<std::string>(r, ""));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      ret[j][i] = arr[i][j];
    }
  }
  return ret;
}

std::vector<std::vector<std::string>> _parse_col(const std::vector<std::string>& lines) {
  std::vector<std::vector<std::string>> arr;
  for (auto& line : lines) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    while (!ss.eof()) {
      std::string elem;
      ss >> elem;
      row.push_back(elem);
    }
    arr.push_back(row);
  }

  return _transpose(arr);
}

void _remove_space(std::string& str) {
  while (str.starts_with(' ')) {
    str = str.substr(1);
  }
  while (str.ends_with(' ')) {
    str.pop_back();
  }
}

std::vector<std::vector<std::string>> _parse_rtl(const std::vector<std::string>& lines) {
  std::vector<std::vector<std::string>> arr;

  std::vector<std::string> cols(lines.front().size());
  for (int j = 0; j < lines.front().size(); j++) {
    for (int i = 0; i < lines.size(); i++) {
      cols[j] += lines[i][j];
    }
  }
  std::reverse(cols.begin(), cols.end());

  std::vector<std::string> elems;
  for (auto& col : cols) {
    std::string op = "";
    if (col.ends_with('*')) {
      op = "*";
    } else if (col.ends_with('+')) {
      op = "+";
    }

    if (!op.empty()) {
      col.pop_back();
    }

    _remove_space(col);

    if (!col.empty()) {
      elems.push_back(col);
    }

    if (!op.empty()) {
      elems.push_back(op);
      arr.push_back(elems);
      elems.clear();
    }
  }

  return arr;
}

uint64_t _calc(const std::vector<std::vector<std::string>>& arr) {
  uint64_t ret = 0;
  for (int i = 0; i < arr.size(); i++) {
    std::string op = arr[i].back();

    if (op == "*") {
      ret += std::accumulate(arr[i].begin(), arr[i].end() - 1,
                             1ULL,
                             [](uint64_t acc, const std::string& str) {
                               return acc * std::stoull(str);
                             });
    } else if (op == "+") {
      ret += std::accumulate(arr[i].begin(), arr[i].end() - 1,
                             0ULL,
                             [](uint64_t acc, const std::string& str) {
                               return acc + std::stoull(str);
                             });
    }
  }
  return ret;
}

uint64_t part1(const std::vector<std::string>& lines) {
  return _calc(_parse_col(lines));
}

uint64_t part2(const std::vector<std::string>& lines) {
  return _calc(_parse_rtl(lines));
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
