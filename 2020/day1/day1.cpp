#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<int> data;

  int curr = 0;
  while (!inputs.eof()) {
    inputs >> curr;
    data.push_back(curr);
  }
  inputs.close();
  return data;
}

std::vector<int> part1(const std::vector<int>& data, int target) {
  std::vector<int> diff;
  std::transform(data.begin(), data.end(), std::back_inserter(diff), [target](int x) { return target - x; });

  for (int i = 0; i < data.size(); i++) {
    if (std::find(data.begin(), data.end(), diff[i]) != data.end()) {
      std::cout << (data[i] * diff[i]) << std::endl;
      break;
    }
  }

  return diff;
}

void part2(std::vector<int>& data) {
  std::vector<int> diff = part1(data, 2020);

  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.size(); j++) {
      if (std::find(data.begin(), data.end(), diff[i] - data[j]) != data.end()) {
        std::cout << (data[i] * data[j] * (diff[i] - data[j])) << std::endl;
        return;
      }
    }
  }
}

int main(int argc, char** argv) {
  std::vector<int> data = readInputs("input.txt");

  part1(data, 2020);
  part2(data);

  return 0;
}