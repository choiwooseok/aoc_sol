#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> readLines(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string line;
  while (std::getline(inputs, line)) {
    data.push_back(line);
  }
  inputs.close();
  return data;
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

void part1(const std::vector<std::string>& data) {
  int cnt = 0;
  for (auto& line : data) {
    std::vector<std::string> parts = split(line, " ");
    std::vector<std::string> range = split(parts[0], "-");
    int least = std::stoi(range[0]);
    int most = std::stoi(range[1]);

    std::string letter = parts[1];
    letter.pop_back();

    std::string password = parts[2];

    int count = std::count(password.begin(), password.end(), letter[0]);
    if (count >= least && count <= most) {
      cnt++;
    }
  }
  std::cout << cnt << std::endl;
}

void part2(std::vector<std::string>& data) {
  int cnt = 0;
  for (auto& line : data) {
    std::vector<std::string> parts = split(line, " ");
    std::vector<std::string> range = split(parts[0], "-");
    int pos1 = std::stoi(range[0]);
    int pos2 = std::stoi(range[1]);

    std::string letter = parts[1];
    letter.pop_back();

    std::string password = parts[2];

    if ((password[pos1 - 1] == letter[0]) ^ (password[pos2 - 1] == letter[0])) {
      cnt++;
    }
  }
  std::cout << cnt << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readLines("input.txt");

  part1(data);
  part2(data);

  return 0;
}