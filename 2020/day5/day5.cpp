#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> readLines(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string line;
  while (std::getline(inputs, line)) {
    data.push_back(line);
  }
  inputs.close();
  return data;
}

void part1(const std::vector<std::string>& data) {
  int highest = 0;

  for (auto& line : data) {
    int rowStart = 0;
    int rowEnd = 127;
    int colStart = 0;
    int colEnd = 7;
    for (int i = 0; i < 7; i++) {
      if (line[i] == 'F') {
        rowEnd = (rowStart + rowEnd) / 2;
      } else {
        rowStart = (rowStart + rowEnd) / 2 + 1;
      }
    }
    for (int i = 7; i < 10; i++) {
      if (line[i] == 'L') {
        colEnd = (colStart + colEnd) / 2;
      } else {
        colStart = (colStart + colEnd) / 2 + 1;
      }
    }
    int seatId = rowStart * 8 + colStart;
    if (seatId > highest) {
      highest = seatId;
    }
  }
  std::cout << highest << std::endl;
}

void part2(std::vector<std::string>& data) {
  std::vector<int> seatIds;

  for (auto& line : data) {
    int rowStart = 0;
    int rowEnd = 127;
    int colStart = 0;
    int colEnd = 7;
    for (int i = 0; i < 7; i++) {
      if (line[i] == 'F') {
        rowEnd = (rowStart + rowEnd) / 2;
      } else {
        rowStart = (rowStart + rowEnd) / 2 + 1;
      }
    }
    for (int i = 7; i < 10; i++) {
      if (line[i] == 'L') {
        colEnd = (colStart + colEnd) / 2;
      } else {
        colStart = (colStart + colEnd) / 2 + 1;
      }
    }
    int seatId = rowStart * 8 + colStart;
    seatIds.push_back(seatId);
  }
  std::sort(seatIds.begin(), seatIds.end());
  for (int i = 0; i < seatIds.size() - 1; i++) {
    if (seatIds[i + 1] - seatIds[i] == 2) {
      std::cout << seatIds[i] + 1 << std::endl;
      break;
    }
  }
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readLines("input.txt");

  part1(data);
  part2(data);

  return 0;
}