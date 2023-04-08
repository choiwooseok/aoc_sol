#include <iostream>
#include <fstream>
#include <vector>

enum class Command {
  FORWARD,
  UP,
  DOWN
};

Command fromStr(const std::string& str) {
  if (str == "forward") {
    return Command::FORWARD;
  } else if (str == "up") {
    return Command::UP;
  } else if (str == "down") {
    return Command::DOWN;
  } else {
    throw std::runtime_error("Unknown command: " + str);
  }
}

std::vector<std::pair<Command, int>> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::pair<Command, int>> data;

  std::string line;
  int unit = 0;
  while (!inputs.eof()) {
    inputs >> line;
    inputs >> unit;
    data.push_back({fromStr(line), unit});
  }
  inputs.close();
  return data;
}

void part1(std::vector<std::pair<Command, int>>& data) {
  int horizontalPosition = 0;
  int depth = 0;
  for (auto elem : data) {
    switch (elem.first) {
      case Command::FORWARD:
        horizontalPosition += elem.second;
        break;
      case Command::UP:
        depth -= elem.second;
        break;
      case Command::DOWN:
        depth += elem.second;
        break;

      default:
        break;
    }
  }
  std::cout << horizontalPosition * depth << std::endl;
}

void part2(std::vector<std::pair<Command, int>>& data) {
  int horizontalPosition = 0;
  int depth = 0;
  int aim = 0;
  for (auto elem : data) {
    switch (elem.first) {
      case Command::FORWARD:
        horizontalPosition += elem.second;
        depth += aim * elem.second;
        break;
      case Command::UP:
        aim -= elem.second;
        break;
      case Command::DOWN:
        aim += elem.second;
        break;

      default:
        break;
    }
    std::cout << horizontalPosition << " " << depth << " " << aim << std::endl;
  }
  std::cout << horizontalPosition * depth << std::endl;
}

int main(int argc, char** argv) {
  // std::vector<std::pair<Command, int>> data = readInputs("day2_test.txt");
  std::vector<std::pair<Command, int>> data = readInputs("day2_input.txt");
  // part1(data);
  part2(data);
  return 0;
}