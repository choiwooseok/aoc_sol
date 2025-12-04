#include <iostream>
#include <format>
#include "../util.h"

std::vector<int> _parse(const std::vector<std::string>& lines) {
  std::vector<int> data;
  for (auto& line : lines) {
    data.push_back(stoi(line));
  }
  return data;
}

int part1(const std::vector<int>& data) {
  int ret = 0;
  for (int i = 0; i < data.size() - 1; i++) {
    if (data[i] < data[i + 1]) {
      ret++;
    }
  }
  return ret;
}

int part2(const std::vector<int>& data) {
  int ret = 0;
  for (int i = 0; i < data.size() - 3; i++) {
    if (data[i] < data[i + 3]) {
      ret++;
    }
  }
  return ret;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day1/input.txt");
  auto data = _parse(lines);

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