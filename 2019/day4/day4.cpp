#include <iostream>
#include "../util.h"

std::vector<int> digit(6);

bool _part1(int pw) {
  for (int i = 0; i < 6; i++) {
    digit[5 - i] = pw % 10;
    pw /= 10;
  }
  bool nonDecrease = true;
  bool hasSameAdj = false;
  for (int i = 0; i < 5; i++) {
    if (digit[i] > digit[i + 1]) {
      nonDecrease = false;
      break;
    }
    if (digit[i] == digit[i + 1]) {
      hasSameAdj = true;
    }
  }
  return hasSameAdj && nonDecrease;
}

int part1(int min, int max) {
  int cnt = 0;

  for (int i = min; i <= max; i++) {
    if (_part1(i)) {
      cnt++;
    }
  }
  return cnt;
}

bool _part2(int pw) {
  for (int i = 0; i < 6; i++) {
    digit[5 - i] = pw % 10;
    pw /= 10;
  }
  bool nonDecrease = true;
  bool hasSameAdj = false;
  for (int i = 0; i < 5; i++) {
    if (digit[i] > digit[i + 1]) {
      nonDecrease = false;
      break;
    }
    if (digit[i] == digit[i + 1]) {
      bool condition = true;
      if (i > 0 && digit[i - 1] == digit[i]) {
        condition = false;
      }
      if (i < 4 && digit[i + 2] == digit[i]) {
        condition = false;
      }
      if (condition) {
        hasSameAdj = true;
      }
    }
  }
  return hasSameAdj && nonDecrease;
}

int part2(int min, int max) {
  int cnt = 0;

  for (int i = min; i <= max; i++) {
    if (_part2(i)) {
      cnt++;
    }
  }
  return cnt;
}

int main(int argc, char** argv) {
  auto line = read_line("day4/input.txt");

  size_t pos = line.find("-");
  int min = std::stoi(line.substr(0, pos));
  int max = std::stoi(line.substr(pos + 1));

  {
    auto [result, ms] = measure_ms(part1, min, max);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, min, max);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}