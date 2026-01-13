#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../util.h"

std::vector<int> readInputs(const std::vector<std::string>& lines) {
  std::vector<int> data;

  int temp_sum = 0;
  for (const auto& line : lines) {
    if (line != "") {
      temp_sum += std::stoi(line);
    } else {
      data.push_back(temp_sum);
      temp_sum = 0;
    }
  }
  if (temp_sum > 0) data.push_back(temp_sum);
  return data;
}

int part1(const std::vector<int>& data) {
  return *std::max_element(data.begin(), data.end());
}

int part2(std::vector<int> data) {
  std::sort(data.begin(), data.end(), std::greater<int>());
  return data[0] + data[1] + data[2];
}

int main(int argc, char** argv) {
  auto lines = read_lines("day1/input.txt");
  auto data = readInputs(lines);

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