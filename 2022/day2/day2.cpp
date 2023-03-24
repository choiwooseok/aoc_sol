#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

enum class RSP {
  R,
  P,
  S
};

std::vector<std::pair<RSP, RSP>> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::pair<RSP, RSP>> data;

  std::string curr;
  int temp_sum = 0;
  while (!inputs.eof()) {
    std::getline(inputs, curr);
    if (curr[0] == 'A') {
      if (curr[2] == 'X') {
        data.push_back({RSP::R, RSP::R});
      }
      if (curr[2] == 'Y') {
        data.push_back({RSP::R, RSP::P});
      }
      if (curr[2] == 'Z') {
        data.push_back({RSP::R, RSP::S});
      }
    }
    if (curr[0] == 'B') {
      if (curr[2] == 'X') {
        data.push_back({RSP::P, RSP::R});
      }
      if (curr[2] == 'Y') {
        data.push_back({RSP::P, RSP::P});
      }
      if (curr[2] == 'Z') {
        data.push_back({RSP::P, RSP::S});
      }
    }
    if (curr[0] == 'C') {
      if (curr[2] == 'X') {
        data.push_back({RSP::S, RSP::R});
      }
      if (curr[2] == 'Y') {
        data.push_back({RSP::S, RSP::P});
      }
      if (curr[2] == 'Z') {
        data.push_back({RSP::S, RSP::S});
      }
    }
  }
  inputs.close();
  return data;
}

void part1(const std::vector<std::pair<RSP, RSP>>& data) {
  int ret = 0;
  for (auto& elem : data) {
    int r = static_cast<int>(elem.second) + 1;

    switch (elem.first) {
      case RSP::R:
        switch (elem.second) {
          case RSP::R:
            r += 3;
            break;
          case RSP::P:
            r += 6;
            break;
          case RSP::S:
            r += 0;
            break;
        }
        break;
      case RSP::P:
        switch (elem.second) {
          case RSP::R:
            r += 0;
            break;
          case RSP::P:
            r += 3;
            break;
          case RSP::S:
            r += 6;
            break;
        }
        break;
      case RSP::S:
        switch (elem.second) {
          case RSP::R:
            r += 6;
            break;
          case RSP::P:
            r += 0;
            break;
          case RSP::S:
            r += 3;
            break;
        }
        break;

      default:
        break;
    }
    ret += r;
  }

  std::cout << ret << std::endl;
}

void part2(const std::vector<std::pair<RSP, RSP>>& data) {
  int ret = 0;
  for (auto& elem : data) {
    int r = 0;
    switch (elem.first) {
      case RSP::R:
        switch (elem.second) {
          case RSP::R:  // lose
            r += static_cast<int>(RSP::S) + 1;
            r += 0;
            break;
          case RSP::P:  // draw
            r += static_cast<int>(RSP::R) + 1;
            r += 3;
            break;
          case RSP::S:  // win
            r += static_cast<int>(RSP::P) + 1;
            r += 6;
            break;
        }
        break;
      case RSP::P:
        switch (elem.second) {
          case RSP::R:  // lose
            r += static_cast<int>(RSP::R) + 1;
            r += 0;
            break;
          case RSP::P:  // draw
            r += static_cast<int>(RSP::P) + 1;
            r += 3;
            break;
          case RSP::S:  // win
            r += static_cast<int>(RSP::S) + 1;
            r += 6;
            break;
        }
        break;
      case RSP::S:
        switch (elem.second) {
          case RSP::R:  // lose
            r += static_cast<int>(RSP::P) + 1;
            r += 0;
            break;
          case RSP::P:  // draw
            r += static_cast<int>(RSP::S) + 1;
            r += 3;
            break;
          case RSP::S:  // win
            r += static_cast<int>(RSP::R) + 1;
            r += 6;
            break;
        }
        break;

      default:
        break;
    }
    ret += r;
  }

  std::cout << ret << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::pair<RSP, RSP>> data = readInputs("input.txt");

  part1(data);
  part2(data);

  return 0;
}