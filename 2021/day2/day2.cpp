#include <iostream>
#include <format>
#include "../util.h"

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

std::vector<std::pair<Command, int>> _parse(const std::string& fileName) {
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

int part1(std::vector<std::pair<Command, int>>& data) {
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
  return horizontalPosition * depth;
}

int part2(std::vector<std::pair<Command, int>>& data) {
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
  }
  return horizontalPosition * depth;
}

int main(int argc, char** argv) {
  std::vector<std::pair<Command, int>> data = _parse("day2/input.txt");

  {
    auto [result, ms] = measure_ms(part1, data);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, data);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}