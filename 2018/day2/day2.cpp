#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
}

int part1(const std::vector<std::string>& lines) {
  int two = 0;
  int three = 0;
  for (const auto& line : lines) {
    std::unordered_map<char, int> m;
    for (auto& ch : line) {
      m[ch]++;
    }
    bool hasTwo = false;
    bool hasThree = false;
    for (auto& [k, v] : m) {
      if (hasTwo && hasThree) break;
      if (v == 2) {
        hasTwo = true;
      }
      if (v == 3) {
        hasThree = true;
      }
    }
    if (hasTwo) two++;
    if (hasThree) three++;
  }
  return two * three;
}

std::string part2(const std::vector<std::string>& lines) {
  for (const auto& line1 : lines) {
    for (const auto& line2 : lines) {
      if (line1 == line2) continue;

      int cnt = 0;
      std::string ret = "";
      for (int i = 0; i < line1.size(); i++) {
        if (line1[i] == line2[i]) {
          ret += line1[i];
        } else {
          cnt++;
        }
      }

      if (cnt == 1) return ret;
    }
  }
  return "";
}

int main(int argc, char** argv) {
  auto lines = read_lines("input.txt");
  std::cout << "part1 : " << part1(lines) << std::endl;
  std::cout << "part2 : " << part2(lines) << std::endl;
  return 0;
}
