#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> digit(6);

bool isValid(int pw, bool partTwo = false) {
  for (int i = 0; i < 6; i++) {
    digit[5 - i] = pw % 10;
    pw /= 10;
  }
  bool nonDecrease = true;
  bool hasSameAdj = false;
  for (int i = 0; i < 5; i++) {
    if (digit[i] > digit[i + 1]) {
      nonDecrease = false;
      break;
    }
    if (!partTwo) {
      if (digit[i] == digit[i + 1]) {
        hasSameAdj = true;
      }
    } else {
      if (digit[i] == digit[i + 1]) {
        bool condition = true;
        if (i > 0 && digit[i - 1] == digit[i]) {
          condition = false;
        }
        if (i < 4 && digit[i + 2] == digit[i]) {
          condition = false;
        }
        if (condition) {
          hasSameAdj = true;
        }
      }
    }
  }
  return hasSameAdj && nonDecrease;
}

int day4(bool partTwo) {
  std::ifstream in("input.txt");
  int rangeMin, rangeMax;
  int cnt = 0;
  if (in.is_open()) {
    std::string temp;
    in >> temp;
    size_t pos = temp.find("-");
    rangeMin = std::stoi(temp.substr(0, pos));
    rangeMax = std::stoi(temp.substr(pos + 1));
    for (int i = rangeMin; i <= rangeMax; i++) {
      if (isValid(i, partTwo)) {
        cnt++;
      }
    }
  }
  return cnt;
}

int main(int argc, char** argv) {
  std::cout << day4(true) << std::endl;
  return 0;
}