#include <iostream>
#include <format>
#include <cmath>
#include <algorithm>
#include <tuple>
#include "../util.h"

std::vector<std::vector<uint64_t>> _merge_intervals(std::vector<std::vector<uint64_t>>& intervals) {
  std::sort(intervals.begin(), intervals.end(), [](std::vector<uint64_t>& a, std::vector<uint64_t>& b) {
    return a[0] < b[0];
  });

  std::vector<std::vector<uint64_t>> ret;
  ret.push_back(intervals.front());

  for (int i = 0; i < intervals.size(); i++) {
    if (ret.back()[1] >= intervals[i][0]) {
      ret.back()[0] = std::min(ret.back()[0], intervals[i][0]);
      ret.back()[1] = std::max(ret.back()[1], intervals[i][1]);
    } else {
      ret.push_back(intervals[i]);
    }
  }
  return ret;
}

// intervals, ids
auto _parse(const std::vector<std::string>& lines) -> std::tuple<std::vector<std::vector<uint64_t>>, std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> intervals;
  std::vector<uint64_t> ids;

  for (auto& line : lines) {
    if (!line.empty()) {
      if (line.find('-') != std::string::npos) {
        auto range = split(line, "-");
        intervals.push_back({std::stoull(range[0]), std::stoull(range[1])});
      } else {
        ids.push_back(std::stoull(line));
      }
    }
  }

  intervals = _merge_intervals(intervals);

  return {intervals, ids};
}

int part1(const std::vector<std::string>& lines) {
  auto [intervals, ids] = _parse(lines);

  int cnt = 0;
  for (auto& id : ids) {
    for (auto& interval : intervals) {
      if (interval[0] <= id && id <= interval[1]) {
        cnt++;
        break;
      }
    }
  }
  return cnt;
}

uint64_t part2(const std::vector<std::string>& lines) {
  auto [intervals, ids] = _parse(lines);

  uint64_t cnt = 0;
  for (auto& interval : intervals) {
    cnt += interval[1] - interval[0] + 1;
  }
  return cnt;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day5/input.txt");

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
