#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<int> > readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string temp;
  while (getline(inputs, temp)) {
    data.push_back(temp);
  }

  inputs.close();

  std::vector<std::vector<int> > map;
  map.resize(data.size());
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      map[i].emplace_back(data[i][j] - '0');
    }
  }

  for (auto row : map) {
    for (auto col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }

  return map;
}

void part1(std::vector<std::vector<int> >& map) {
}

void part2(std::vector<std::vector<int> >& map) {
}

int main(int argc, char** argv) {
  std::vector<std::vector<int> > data = readInputs("day9_test.txt");
  // std::vector<std::vector<int> > data = readInputs("day9_input.txt");
  part1(data);
  part2(data);
  return 0;
}