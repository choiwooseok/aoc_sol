#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

std::vector<std::vector<std::string>> readLines(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::vector<std::string>> data;

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputs, line)) {
    if (line != "") {
      lines.push_back(line);
    } else {
      data.push_back(lines);
      lines.clear();
    }
  }
  inputs.close();
  return data;
}

void part1(const std::vector<std::vector<std::string>>& data) {
  int cnt = 0;
  for (auto& group : data) {
    std::unordered_set<char> answers;
    for (auto& line : group) {
      for (auto& c : line) {
        answers.insert(c);
      }
    }
    cnt += answers.size();
  }
  std::cout << cnt << std::endl;
}

void part2(std::vector<std::vector<std::string>>& data) {
  int cnt = 0;
  for (auto& group : data) {
    std::unordered_set<char> answers;
    for (auto& c : group[0]) {
      answers.insert(c);
    }
    for (int i = 1; i < group.size(); i++) {
      std::unordered_set<char> temp;
      for (auto& c : group[i]) {
        temp.insert(c);
      }
      std::unordered_set<char> intersection;
      for (auto& c : answers) {
        if (temp.find(c) != temp.end()) {
          intersection.insert(c);
        }
      }
      answers = intersection;
    }
    cnt += answers.size();
  }
  std::cout << cnt << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::vector<std::string>> data = readLines("input.txt");

  part1(data);
  part2(data);

  return 0;
}