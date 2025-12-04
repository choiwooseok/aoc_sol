#include <iostream>
#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>

#include "../util.h"

std::vector<int> _parse(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<int> data;

  std::string line;
  std::string temp;
  while (getline(inputs, temp, ',')) {
    data.push_back(std::stoi(temp));
  }
  inputs.close();
  return data;
}

int part1(std::vector<int>& data) {
  auto fuels = std::numeric_limits<int>::max();
  for (int i = 0; i < data.size(); i++) {
    int temp = 0;
    for (int j = 0; j < data.size(); j++) {
      temp += std::abs(data[j] - data[i]);
    }

    if (temp < fuels) {
      fuels = temp;
    }
  }

  return fuels;
}

int64_t part2_helper(std::vector<int>& data, int64_t target) {
  int64_t fuels = 0;
  for (auto& elem : data) {
    int64_t n = std::abs(elem - target);
    fuels += (n * (n + 1)) / 2;
  }
  return fuels;
}

int64_t part2(std::vector<int>& data) {
  int64_t min = *std::min_element(data.begin(), data.end());
  int64_t max = *std::max_element(data.begin(), data.end());

  int64_t ret = std::numeric_limits<int64_t>::max();
  for (int64_t i = min; i <= max; i++) {
    ret = std::min(ret, part2_helper(data, i));
  }
  return ret;
}

int main(int argc, char** argv) {
  std::vector<int> data = _parse("day7/input.txt");

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