#pragma once

#include <chrono>
#include <functional>
#include <vector>
#include <fstream>
#include <string>

template <typename T, typename F>
auto operator|(T&& arg, F&& func)
    -> decltype(std::invoke(std::forward<F>(func), std::forward<T>(arg))) {
  return std::invoke(std::forward<F>(func), std::forward<T>(arg));
}

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

std::vector<std::string> split(const std::string& source, const std::string& delim) {
  size_t pos_start = 0, pos_end, delim_len = delim.length();
  std::vector<std::string> res;

  while ((pos_end = source.find(delim, pos_start)) != std::string::npos) {
    std::string token = source.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(source.substr(pos_start));
  return res;
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
