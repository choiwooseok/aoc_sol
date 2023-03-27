#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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

std::vector<std::string> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string line;
  while (!inputs.eof()) {
    std::getline(inputs, line);
    data.push_back(line);
  }
  inputs.close();
  return data;
}

void part1(const std::vector<std::string>& data) {
  int cnt = 0;
  for (auto& elem : data) {
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
  std::cout << cnt << std::endl;
}

void part2(const std::vector<std::string>& data) {
  int cnt = 0;
  for (auto& elem : data) {
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
  std::cout << cnt << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readInputs("input.txt");
  part1(data);
  part2(data);
  return 0;
}