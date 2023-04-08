#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int fuel(int mass) {
  return std::round(mass / 3) - 2;
}

void part1() {
  std::string tmp;
  std::fstream fs("input.txt");
  long long sum = 0LL;
  while (std::getline(fs, tmp)) {
    sum += fuel(std::stoi(tmp));
  }
  std::cout << sum << std::endl;
}

void part2() {
  std::string tmp;
  std::fstream fs("input.txt");
  long long sum = 0LL;
  while (std::getline(fs, tmp)) {
    int temp = std::stoi(tmp);
    while (temp > 0) {
      int calc = std::round(temp / 3) - 2;
      sum += calc < 0 ? 0 : calc;
      temp = calc;
    }
  }
  std::cout << sum << std::endl;
}

int main(int argc, char** argv) {
  part1();
  part2();
  return 0;
}
