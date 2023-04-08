#include <iostream>
#include <fstream>
#include <vector>

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

void part1(const std::vector<int>& data) {
  int ret = 0;
  for (int i = 0; i < data.size() - 1; i++) {
    if (data[i] < data[i + 1]) {
      ret++;
    }
  }
  std::cout << ret << std::endl;
}

void part2(const std::vector<int>& data) {
  int ret = 0;
  for (int i = 0; i < data.size() - 3; i++) {
    if (data[i] + data[i + 1] + data[i + 2] < data[i + 1] + data[i + 2] + data[i + 3]) {
      ret++;
    }
  }
  std::cout << ret << std::endl;
}

int main(int argc, char** argv) {
  // std::vector<int> data = readInputs("day1_test.txt");
  std::vector<int> data = readInputs("day1_input.txt");

  part1(data);
  part2(data);

  return 0;
}