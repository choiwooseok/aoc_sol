#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>

std::vector<int> readInputs(const std::string& fileName) {
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

void part1(std::vector<int>& data) {
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

  std::cout << fuels << std::endl;
}

int64_t part2_helper(std::vector<int>& data, int64_t target) {
  int64_t fuels = 0;
  for (auto& elem : data) {
    int64_t n = std::abs(elem - target);
    fuels += (n * (n + 1)) / 2;
  }
  return fuels;
}

void part2(std::vector<int>& data) {
  int64_t min = *std::min_element(data.begin(), data.end());
  int64_t max = *std::max_element(data.begin(), data.end());

  int64_t ret = std::numeric_limits<int64_t>::max();
  for (int64_t i = min; i <= max; i++) {
    ret = std::min(ret, part2_helper(data, i));
  }
  std::cout << ret << std::endl;
}

int main(int argc, char** argv) {
  // std::vector<int> data = readInputs("day7_test.txt");
  std::vector<int> data = readInputs("day7_input.txt");
  part1(data);
  part2(data);
  return 0;
}