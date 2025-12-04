#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "../util.h"

std::vector<std::pair<std::string, std::string>> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::pair<std::string, std::string>> data;
  std::string line;
  while (std::getline(inputs, line)) {
    if (line.empty()) continue;
    auto sep = line.find('|');
    data.emplace_back(line.substr(0, sep), line.substr(sep + 1));
  }
  inputs.close();
  return data;
}

static int mask_of(const std::string& s) {
  int m = 0;
  for (char c : s)
    if (c >= 'a' && c <= 'g') m |= 1 << (c - 'a');
  return m;
}

int part1(std::vector<std::pair<std::string, std::string>>& data) {
  int cnt = 0;
  for (auto& entry : data) {
    std::istringstream ss(entry.second);
    std::string tok;
    while (ss >> tok) {
      int len = tok.size();
      if (len == 2 || len == 3 || len == 4 || len == 7) ++cnt;
    }
  }
  return cnt;
}

// 비트마스크 기반 결정적 해법
int part2(std::vector<std::pair<std::string, std::string>>& data) {
  long long total = 0;
  for (auto& entry : data) {
    std::istringstream ps(entry.first);
    std::vector<int> patterns;
    std::string tok;
    while (ps >> tok) patterns.push_back(mask_of(tok));

    // 식별용 컨테이너
    std::array<int, 10> digit_mask{};
    std::vector<int> len5, len6;

    // 기본 식별(길이로 1,4,7,8 고정)
    for (int m : patterns) {
      int bits = __builtin_popcount((unsigned)m);
      if (bits == 2)
        digit_mask[1] = m;
      else if (bits == 3)
        digit_mask[7] = m;
      else if (bits == 4)
        digit_mask[4] = m;
      else if (bits == 7)
        digit_mask[8] = m;
      else if (bits == 5)
        len5.push_back(m);  // 2,3,5
      else if (bits == 6)
        len6.push_back(m);  // 0,6,9
    }

    // 9: len6 중에서 4를 포함하는 것
    for (auto it = len6.begin(); it != len6.end(); ++it) {
      if (((*it) & digit_mask[4]) == digit_mask[4]) {
        digit_mask[9] = *it;
        len6.erase(it);
        break;
      }
    }
    // 0: 남은 len6 중 1을 포함하는 것
    for (auto it = len6.begin(); it != len6.end(); ++it) {
      if (((*it) & digit_mask[1]) == digit_mask[1]) {
        digit_mask[0] = *it;
        len6.erase(it);
        break;
      }
    }
    // 남은 len6는 6
    if (!len6.empty()) {
      digit_mask[6] = len6.front();
      len6.clear();
    }

    // 3: len5 중 1을 포함하는 것
    for (auto it = len5.begin(); it != len5.end(); ++it) {
      if (((*it) & digit_mask[1]) == digit_mask[1]) {
        digit_mask[3] = *it;
        len5.erase(it);
        break;
      }
    }
    // 5: len5 중 6이 모두 포함하는 것 (6에서 5의 비트가 모두 켜짐)
    for (auto it = len5.begin(); it != len5.end(); ++it) {
      if (((digit_mask[6]) & (*it)) == *it) {
        digit_mask[5] = *it;
        len5.erase(it);
        break;
      }
    }
    // 남은 len5는 2
    if (!len5.empty()) {
      digit_mask[2] = len5.front();
      len5.clear();
    }

    std::unordered_map<int, int> mask2digit;
    for (int d = 0; d <= 9; ++d) mask2digit[digit_mask[d]] = d;

    // 출력 디코드
    std::istringstream os(entry.second);
    long long value = 0;
    while (os >> tok) {
      int m = mask_of(tok);
      value = value * 10 + mask2digit[m];
    }
    total += value;
  }
  return static_cast<int>(total);
}

int main(int argc, char** argv) {
  auto data = readInputs("day8/input.txt");

  {
    auto [res, ms] = measure_ms(part1, data);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", res, ms);
  }

  {
    auto [res, ms] = measure_ms(part2, data);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", res, ms);
  }

  return 0;
}