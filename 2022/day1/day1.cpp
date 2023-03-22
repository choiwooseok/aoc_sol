#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<int> data;

  std::string curr;
  int temp_sum = 0;
  while (!inputs.eof()) {
    std::getline(inputs, curr);
    if (curr != "") {
      temp_sum += std::stoi(curr);
    } else {
      data.push_back(temp_sum);
      temp_sum = 0;
    }
  }
  inputs.close();
  return data;
}

void part1(const std::vector<int>& data) {
  std::cout << *std::max_element(data.begin(), data.end()) << std::endl;
}

void part2(std::vector<int>& data) {
  std::sort(data.begin(), data.end(), std::greater<int>());
  std::cout << (data[0] + data[1] + data[2]) << std::endl;
}

int main(int argc, char** argv) {
  std::vector<int> data = readInputs("input.txt");

  part1(data);
  part2(data);

  return 0;
}