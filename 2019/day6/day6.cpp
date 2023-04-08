#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

std::map<std::string, std::set<std::string> > inputs;

int count(const std::string& node, int lvl) {
  int cnt = lvl;
  for (auto& elem : inputs[node]) {
    cnt += count(elem, lvl + 1);
  }
  return cnt;
}

void printDirect() {
  for (auto& input : inputs) {
    std::cout << input.first << " : ";
    for (auto& elem : input.second) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv) {
  bool isTest = true;
  std::fstream fs(isTest ? "test.txt" : "input.txt");
  std::string tmp;
  while (std::getline(fs, tmp)) {
    int idx = tmp.find(')');
    std::string first = tmp.substr(0, idx);
    std::string second = tmp.substr(idx + 1);
    inputs[first].insert(second);
  }
  std::cout << count("COM", 0) << std::endl;
  fs.close();
  // printDirect();
  return 0;
}