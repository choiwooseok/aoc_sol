#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

std::string readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);

  std::string line;
  while (!inputs.eof()) {
    std::getline(inputs, line);
  }
  return line;
}

void part1(const std::string& data) {
  for (int i = 0; i < data.length() - 3; i++) {
    std::unordered_set<char> set;
    for (int j = 0; j < 4; j++) {
      set.insert(data[i + j]);
    }
    if (set.size() == 4) {
      std::cout << i + 4 << std::endl;
      break;
    }
  }
}

void part2(const std::string& data) {
  for (int i = 0; i < data.length() - 13; i++) {
    std::unordered_set<char> set;
    for (int j = 0; j < 14; j++) {
      set.insert(data[i + j]);
    }

    if (set.size() == 14) {
      std::cout << i + 14 << std::endl;
      break;
    }
  }
}

int main(int argc, char** argv) {
  std::string data = readInputs("input.txt");
  part1(data);
  part2(data);
  return 0;
}