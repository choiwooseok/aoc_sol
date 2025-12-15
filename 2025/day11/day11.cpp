#include <iostream>
#include <format>
#include <unordered_map>

#include "../util.h"

std::unordered_map<std::string, std::vector<std::string>> _parse(const std::vector<std::string>& lines) {
  std::unordered_map<std::string, std::vector<std::string>> m;
  for (auto& line : lines) {
    std::string device = line.substr(0, 3);
    auto outputs = split(line.substr(5), " ");
    m[device] = outputs;
  }
  return m;
}

uint64_t _part1(const std::unordered_map<std::string, std::vector<std::string>>& nodes,
                std::vector<std::string>& path,
                const std::string& from,
                const std::string& to) {
  const auto outputs = nodes.at(from);
  if (std::find(outputs.begin(), outputs.end(), to) != outputs.end()) {
    return 1;
  }

  if (std::find(path.begin(), path.end(), from) != path.end()) {
    return 0;
  }

  uint64_t cnt = 0;
  path.push_back(from);
  for (const auto& output : outputs) {
    cnt += _part1(nodes, path, output, to);
  }
  path.pop_back();
  return cnt;
}

uint64_t part1(const std::vector<std::string>& lines) {
  auto nodes = _parse(lines);
  std::vector<std::string> path;
  return _part1(nodes, path, "you", "out");
}

uint64_t _part2(const std::unordered_map<std::string, std::vector<std::string>>& nodes,
                std::unordered_map<std::string, uint64_t>& cache,
                const std::string& from,
                const std::string& to,
                bool fft,
                bool dac) {
  std::string cache_key = from + "_" + std::to_string(fft) + "_" + std::to_string(dac);
  if (cache.count(cache_key)) return cache[cache_key];

  if (from == "fft") fft = true;
  if (from == "dac") dac = true;

  const auto outputs = nodes.at(from);
  if (std::find(outputs.begin(), outputs.end(), to) != outputs.end()) {
    return (fft && dac) ? 1 : 0;
  }

  uint64_t cnt = 0;
  for (const auto& output : outputs) {
    cnt += _part2(nodes, cache, output, to, fft, dac);
  }
  cache[cache_key] = cnt;

  return cnt;
}

uint64_t part2(const std::vector<std::string>& lines) {
  auto nodes = _parse(lines);
  std::unordered_map<std::string, uint64_t> cache;
  return _part2(nodes, cache, "svr", "out", false, false);
}

int main(int argc, char** argv) {
  auto lines = read_lines("day11/input.txt");

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