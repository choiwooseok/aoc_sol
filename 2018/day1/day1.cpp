#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>

std::vector<std::string> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string curr;
  while (std::getline(inputs, curr)) {
    data.push_back(curr);
  }
  inputs.close();
  return data;
}

int part1(int start, const std::vector<std::string>& lines) {
  int ret = start;
  for (const auto& line : lines) {
    ret += stoi(line);
  }
  return ret;
}

int part2(int start, const std::vector<std::string>& lines) {
  std::unordered_set<int> seen{start};

  int ret = start;
  while (true) {
    for (const auto& line : lines) {
      ret += stoi(line);
      if (seen.count(ret)) {
        return ret;
      }
      seen.insert(ret);
    }
  }
  return -1;
}

int main(int argc, char** argv) {
  auto lines = readInputs("input.txt");
  std::cout << "part1 : " << part1(0, lines) << std::endl;
  std::cout << "part2 : " << part2(0, lines) << std::endl;
  return 0;
}
