#include <iostream>
#include <format>
#include <set>
#include "../util.h"

bool isOpposite(char a, char b) {
  return std::tolower(a) == std::tolower(b) && a != b;
}

std::string part1(const std::string& line) {
  std::string ret;
  for (char ch : line) {
    if (!ret.empty() && isOpposite(ch, ret.back())) {
      ret.pop_back();
    } else {
      ret.push_back(ch);
    }
  }
  return ret;
}

std::string part2(const std::string& line) {
  std::set<char> chars(line.begin(), line.end());

  std::string min = line;
  for (char ch : chars) {
    std::string temp;
    for (char c : line) {
      if (std::tolower(c) != ch) {
        temp.push_back(c);
      }
    }

    temp = part1(temp);
    if (min.size() > temp.size()) {
      min = temp;
    }
  }

  return min;
}

int main(int argc, char** argv) {
  auto line = read_line("day5/input.txt");

  {
    auto [result, ms] = measure_ms(part1, line);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result.size(), ms);
  }

  {
    auto [result, ms] = measure_ms(part2, line);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result.size(), ms);
  }

  return 0;
}
