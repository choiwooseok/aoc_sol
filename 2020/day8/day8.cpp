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

std::vector<std::string> split(const std::string& source, const std::string& delim) {
  size_t pos_start = 0, pos_end, delim_len = delim.length();
  std::vector<std::string> res;

  while ((pos_end = source.find(delim, pos_start)) != std::string::npos) {
    std::string token = source.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(source.substr(pos_start));
  return res;
}

void part1(const std::vector<std::string>& data) {
  int acc = 0;
  std::vector<int> visited;
  for (int i = 0; i < data.size(); i++) {
    std::vector<std::string> parts = split(data[i], " ");
    std::string opCode = parts[0];
    std::string arg = parts[1];

    if (std::find(visited.begin(), visited.end(), i) != visited.end()) {
      break;
    }

    visited.push_back(i);

    if (opCode == "nop") {
      continue;
    } else if (opCode == "jmp") {
      i += std::stoi(arg) - 1;
    } else if (opCode == "acc") {
      acc += std::stoi(arg);
    }
  }

  std::cout << acc << std::endl;
}

void part2(std::vector<std::string>& data) {
  int acc = 0;
  for (int i = 0; i < data.size(); i++) {
    std::vector<std::string> parts = split(data[i], " ");
    std::string opCode = parts[0];
    std::string arg = parts[1];

    if (opCode == "nop") {
      parts[0] = "jmp";
    } else if (opCode == "jmp") {
      parts[0] = "nop";
    } else {
      continue;
    }

    std::vector<std::string> temp = data;
    temp[i] = parts[0] + " " + parts[1];

    int acc = 0;
    std::vector<int> visited;
    for (int j = 0; j < temp.size(); j++) {
      std::vector<std::string> parts = split(temp[j], " ");
      std::string opCode = parts[0];
      std::string arg = parts[1];

      if (std::find(visited.begin(), visited.end(), j) != visited.end()) {
        break;
      }

      visited.push_back(j);

      if (opCode == "nop") {
        continue;
      } else if (opCode == "jmp") {
        j += std::stoi(arg) - 1;
      } else if (opCode == "acc") {
        acc += std::stoi(arg);
      }

      if (j == temp.size() - 1) {
        std::cout << acc << std::endl;
        return;
      }
    }
  }
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readLines("input.txt");

  part1(data);
  part2(data);

  return 0;
}