#pragma once

#include <chrono>
#include <functional>
#include <vector>
#include <fstream>
#include <string>

std::string read_line(const std::string& fileName) {
  std::ifstream fs(fileName);
  std::string curr;
  std::getline(fs, curr);
  return curr;
}

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
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
