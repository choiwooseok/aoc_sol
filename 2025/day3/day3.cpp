#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <format>
#include <chrono>

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
}

// slow
// int part1(const std::vector<std::string>& lines) {
//   int sum = 0;
//   for (const auto& line : lines) {
//     int max = -1;
//     for (int i = 0; i < line.size() - 1; i++) {
//       for (int j = i + 1; j < line.size(); j++) {
//         int curr = (line[i] - '0') * 10 + (line[j] - '0');
//         if (curr >= max) {
//           max = curr;
//         }
//       }
//     }
//     sum += max;
//   }
//   return sum;
// }

// slow
// void _part2_back(const std::string& line, int idx, int need, std::string curr, std::string& max) {
//   if (idx >= line.size()) return;
//   if (line.size() - idx < need) return;
//   if (need == 0) {
//     if (curr >= max) max = curr;
//     return;
//   }

//   curr.push_back(line[idx]);
//   _part2_back(line, idx + 1, need - 1, curr, max);
//   curr.pop_back();
//   _part2_back(line, idx + 1, need, curr, max);
// }

// uint64_t part2(const std::vector<std::string>& lines) {
//   uint64_t sum = 0;
//   for (const auto& line : lines) {
//     std::string max = "0";
//     _part2_back(line, 0, 12, "", max);
//     sum += std::stoull(max);
//   }
//   return sum;
// }

std::string greedy_upper_bound(const std::string& digits, int start_pos, int required_count) {
  int total_size = (int)digits.size();
  if (total_size - start_pos < required_count) return std::string(required_count, '0');

  std::string result;
  result.reserve(required_count);
  int current_pos = start_pos;
  int remaining_needed = required_count;

  while (remaining_needed > 0) {
    int available = total_size - current_pos;
    int can_skip = available - remaining_needed;  // 마지막까지 스캔 가능한 거리

    int best_idx = current_pos;
    char best_digit = digits[current_pos];
    int scan_limit = current_pos + can_skip;

    for (int i = current_pos; i <= scan_limit; ++i) {
      if (digits[i] > best_digit) {
        best_digit = digits[i];
        best_idx = i;
        if (best_digit == '9') break;
      }
    }

    result.push_back(best_digit);
    current_pos = best_idx + 1;
    --remaining_needed;
  }
  return result;
}

void _backtrack_greedy(const std::string& s, int pos, int need, std::string curr, std::string& best, int k) {
  if (need == 0) {
    if (curr > best) best = curr;
    return;
  }
  if (s.size() - pos < need) return;

  // 현재 prefix + greedy upper
  std::string upper = curr + greedy_upper_bound(s, pos, need);
  if (upper <= best) return;

  // 큰 숫자부터 선택 (9..1). 동일 숫자 여러 위치 중복 제거
  char last = 0;
  for (char d = '9'; d >= '1'; --d) {
    if (d == last) continue;
    int limit = s.size() - need;
    int idx = -1;
    for (int i = pos; i <= limit; ++i) {
      if (s[i] == d) {
        idx = i;
        break;
      }
    }
    if (idx == -1) continue;
    last = d;

    curr.push_back(d);
    _backtrack_greedy(s, idx + 1, need - 1, curr, best, k);
    curr.pop_back();
    if (best.size() == k) return;
  }
}

uint64_t backtrack_greedy(const std::vector<std::string>& lines, int need) {
  uint64_t sum = 0;
  for (const auto& line : lines) {
    std::string max = "0";
    _backtrack_greedy(line, 0, need, "", max, need);
    sum += std::stoull(max);
  }
  return sum;
}

int main(int argc, char** argv) {
  using namespace std::chrono;

  auto lines = read_lines("day3/input.txt");

  {
    auto begin = system_clock::now();
    std::cout << std::format("part1 : {}\n", backtrack_greedy(lines, 2));
    auto end = system_clock::now();
    std::cout << std::format(" - elapsed : {} ms\n", duration_cast<milliseconds>(end - begin).count());
  }

  {
    auto begin = system_clock::now();
    std::cout << std::format("part2 : {}\n", backtrack_greedy(lines, 12));
    auto end = system_clock::now();
    std::cout << std::format(" - elapsed : {} ms\n", duration_cast<milliseconds>(end - begin).count());
  }

  return 0;
}
