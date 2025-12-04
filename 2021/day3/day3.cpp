#include <iostream>
#include <format>
#include <map>

#include "../util.h"

int binaryToDecimal(const std::string& n) {
  std::string num = n;
  int dec_value = 0;
  int base = 1;

  int len = num.length();
  for (int i = len - 1; i >= 0; i--) {
    if (num[i] == '1')
      dec_value += base;
    base = base * 2;
  }

  return dec_value;
}

// key -> index
// value {0 cnt, 1 cnt}
std::map<int, std::pair<int, int> > countHelper(const std::vector<std::string>& data) {
  std::map<int, std::pair<int, int> > counts;
  for (auto& elem : data) {
    for (int i = 0; i < elem.size(); i++) {
      if (elem[i] == '0') {
        counts[i].first++;
      } else {
        counts[i].second++;
      }
    }
  }
  return counts;
}

std::pair<std::string, std::string> getGammaNEpsilon(std::map<int, std::pair<int, int> >& counts) {
  std::string gamma = "";
  std::string epsilon = "";
  for (auto& count : counts) {
    int zeros = count.second.first;
    int ones = count.second.second;

    gamma.append(std::to_string(zeros > ones ? 0 : 1));
    epsilon.append(std::to_string(zeros > ones ? 1 : 0));
  }
  return {gamma, epsilon};
}

int part1(std::vector<std::string>& data) {
  std::map<int, std::pair<int, int> > counts = countHelper(data);
  std::pair<std::string, std::string> ge = getGammaNEpsilon(counts);
  return binaryToDecimal(ge.first) * binaryToDecimal(ge.second);
}

std::vector<std::string> filter(std::vector<std::string>& data, int idx, bool most) {
  std::map<int, std::pair<int, int> > counts = countHelper(data);

  int zeros = counts[idx].first;
  int ones = counts[idx].second;

  char target;
  if (most) {
    target = zeros > ones ? '0' : '1';
  } else {
    target = zeros > ones ? '1' : '0';
  }

  std::vector<std::string> filtered;

  for (auto& elem : data) {
    if (elem[idx] == target) {
      filtered.push_back(elem);
    }
  }
  return filtered;
}

int part2(std::vector<std::string>& data) {
  int idx = 0;
  std::vector<std::string> oxy = filter(data, idx, true);
  idx++;
  while (oxy.size() > 1) {
    oxy = filter(oxy, idx, true);
    idx++;
  }

  idx = 0;
  std::vector<std::string> co2 = filter(data, idx, false);
  idx++;
  while (co2.size() > 1) {
    co2 = filter(co2, idx, false);
    idx++;
  }

  return binaryToDecimal(oxy[0]) * binaryToDecimal(co2[0]);
}

int main(int argc, char** argv) {
  std::vector<std::string> data = read_lines("day3/input.txt");

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