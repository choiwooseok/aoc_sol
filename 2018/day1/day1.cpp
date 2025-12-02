#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
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
  auto lines = read_lines("input.txt");
  std::cout << "part1 : " << part1(0, lines) << std::endl;
  std::cout << "part2 : " << part2(0, lines) << std::endl;
  return 0;
}
