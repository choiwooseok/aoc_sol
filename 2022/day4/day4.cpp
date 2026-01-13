#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../util.h"

int part1(const std::vector<std::string>& lines) {
  int cnt = 0;
  for (auto& elem : lines) {
    auto pairs = split(elem, ",");
    auto l = split(pairs[0], "-");
    auto r = split(pairs[1], "-");

    std::vector<int> l_elems;
    std::vector<int> r_elems;

    for (int i = std::stoi(l[0]); i <= std::stoi(l[1]); i++) {
      l_elems.push_back(i);
    }

    for (int i = std::stoi(r[0]); i <= std::stoi(r[1]); i++) {
      r_elems.push_back(i);
    }

    if (l_elems.size() > r_elems.size()) {
      std::swap(l_elems, r_elems);
    }

    bool found = false;
    for (int elem : l_elems) {
      auto iter = std::find(r_elems.begin(), r_elems.end(), elem);
      if (iter == r_elems.end()) {
        found = false;
        break;
      } else {
        found = true;
      }
    }

    if (found) {
      cnt++;
    }
  }
  return cnt;
}

int part2(const std::vector<std::string>& lines) {
  int cnt = 0;
  for (auto& elem : lines) {
    auto pairs = split(elem, ",");
    auto l = split(pairs[0], "-");
    auto r = split(pairs[1], "-");

    std::vector<int> l_elems;
    std::vector<int> r_elems;

    for (int i = std::stoi(l[0]); i <= std::stoi(l[1]); i++) {
      l_elems.push_back(i);
    }

    for (int i = std::stoi(r[0]); i <= std::stoi(r[1]); i++) {
      r_elems.push_back(i);
    }

    if (l_elems.size() > r_elems.size()) {
      std::swap(l_elems, r_elems);
    }

    bool found = false;
    for (int elem : l_elems) {
      auto iter = std::find(r_elems.begin(), r_elems.end(), elem);
      if (iter != r_elems.end()) {
        found = true;
      }
    }

    if (found) {
      cnt++;
    }
  }
  return cnt;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day4/input.txt");

  {
    auto [result, ms] = measure_ms(part1, lines);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, lines);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}