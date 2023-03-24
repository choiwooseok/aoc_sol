#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string line;
  while (!inputs.eof()) {
    std::getline(inputs, line);
    data.push_back(line);
  }
  inputs.close();
  return data;
}

int getPriorities(char ch) {
  if ('a' <= ch && ch <= 'z') {
    return ch - '0' - 48;
  } else {
    return ch - '0' + 10;
  }
}

void part1(const std::vector<std::string>& data) {
  int ret = 0;
  for (auto& line : data) {
    std::string elem0 = line.substr(0, line.length() / 2);
    std::string elem1 = line.substr(line.length() / 2);

    for (char ch : elem0) {
      if (std::find(elem1.begin(), elem1.end(), ch) != elem1.end()) {
        ret += getPriorities(ch);
        break;
      }
    }
  }

  std::cout << ret << std::endl;
}

void part2(const std::vector<std::string>& data) {
  int ret = 0;
  for (int i = 0; i < data.size(); i += 3) {
    for (char ch : data[i]) {
      if (std::find(data[i + 1].begin(), data[i + 1].end(), ch) != data[i + 1].end()) {
        if (std::find(data[i + 2].begin(), data[i + 2].end(), ch) != data[i + 2].end()) {
          ret += getPriorities(ch);
          break;
        }
      }
    }
  }

  std::cout << ret << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readInputs("input.txt");
  part1(data);
  part2(data);
  return 0;
}