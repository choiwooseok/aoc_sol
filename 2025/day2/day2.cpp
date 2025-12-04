#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cstdint>
#include <numeric>
#include <format>
#include "../util.h"

static uint64_t pow10(int k) {
  uint64_t r = 1;
  while (k-- > 0) r *= 10;
  return r;
}

static uint64_t ceil_div(uint64_t a, uint64_t b) {
  return (a + b - 1) / b;
}

static std::vector<std::pair<uint64_t, uint64_t>> parse_ranges(const std::string& line) {
  std::vector<std::pair<uint64_t, uint64_t>> ranges;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, ',')) {
    if (token.empty()) continue;
    auto pos = token.find('-');
    uint64_t lo = std::stoull(token.substr(0, pos));
    uint64_t hi = std::stoull(token.substr(pos + 1));
    ranges.emplace_back(lo, hi);
  }
  return ranges;
}

// generate all repeated-block numbers within [lo, hi] for repetition count >=2
static std::unordered_set<uint64_t> generate_repeated_in_range(uint64_t lo, uint64_t hi) {
  std::unordered_set<uint64_t> out;
  int max_digits = std::to_string(hi).size();

  // total length n (number of digits) from 2..max_digits
  for (int n = 2; n <= max_digits; ++n) {
    for (int k = 1; k <= n / 2; ++k) {
      if (n % k != 0) continue;  // k must divide n
      int r = n / k;
      if (r < 2) continue;

      uint64_t pow10k = pow10(k);
      uint64_t pow10n = pow10(n);
      uint64_t denom = pow10k - 1;  // >0 since k>=1
      if (denom == 0) continue;
      uint64_t base_r = (pow10n - 1) / denom;

      uint64_t s_min = pow10(k - 1);
      uint64_t s_max = pow10k - 1;

      uint64_t s_lo = ceil_div(lo, base_r);
      uint64_t s_hi = hi / base_r;
      if (s_hi < s_lo) continue;
      if (s_lo < s_min) s_lo = s_min;
      if (s_hi > s_max) s_hi = s_max;
      if (s_hi < s_lo) continue;

      for (uint64_t s = s_lo; s <= s_hi; ++s) {
        uint64_t cand = s * base_r;
        if (cand < lo || cand > hi) continue;
        out.insert(cand);
      }
    }
  }
  return out;
}

uint64_t part1(const std::string& line) {
  auto ranges = parse_ranges(line);
  std::unordered_set<uint64_t> invalids;
  for (auto& rg : ranges) {
    uint64_t lo = rg.first, hi = rg.second;
    int max_digits = std::to_string(hi).size();
    // k from 1..max_digits/2
    for (int k = 1; k <= max_digits / 2; ++k) {
      uint64_t pow10k = pow10(k);
      uint64_t base = pow10k + 1;  // for r==2

      uint64_t s_min = pow10(k - 1);
      uint64_t s_max = pow10k - 1;

      uint64_t s_lo = ceil_div(lo, base);
      uint64_t s_hi = hi / base;
      if (s_hi < s_lo) continue;
      if (s_lo < s_min) s_lo = s_min;
      if (s_hi > s_max) s_hi = s_max;
      if (s_hi < s_lo) continue;

      for (uint64_t s = s_lo; s <= s_hi; ++s) {
        uint64_t cand = s * base;
        if (cand < lo || cand > hi) continue;
        invalids.insert(cand);
      }
    }
  }

  return std::accumulate(invalids.begin(), invalids.end(), 0ULL);
}

uint64_t part2(const std::string& line) {
  auto ranges = parse_ranges(line);
  std::unordered_set<uint64_t> invalids;
  for (auto& rg : ranges) {
    auto s = generate_repeated_in_range(rg.first, rg.second);
    invalids.insert(s.begin(), s.end());
  }
  return std::accumulate(invalids.begin(), invalids.end(), 0ULL);
}

int main(int argc, char** argv) {
  auto line = read_line("day2/input.txt");

  {
    auto [result, ms] = measure_ms(part1, line);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, line);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}
