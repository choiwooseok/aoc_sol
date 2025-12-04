#pragma once

#include <chrono>
#include <functional>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
}

std::string read_line(const std::string& fileName) {
  return read_lines(fileName)[0];
}

template <typename F, typename... Args>
auto measure_ms(F&& fn, Args&&... args)
    -> std::pair<std::invoke_result_t<F, Args...>, long long> {
  using namespace std::chrono;
  auto start = system_clock::now();
  auto result = std::invoke(std::forward<F>(fn), std::forward<Args>(args)...);
  auto end = system_clock::now();
  long long ms = duration_cast<milliseconds>(end - start).count();
  return {result, ms};
}
