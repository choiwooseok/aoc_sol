#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

std::vector<std::pair<std::string, std::string> > readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::pair<std::string, std::string> > data;

  std::string delim = "|";

  std::string temp;
  while (getline(inputs, temp)) {
    data.push_back({temp.substr(0, temp.find(delim) - 1), temp.substr(temp.find(delim) + 2)});
  }

  inputs.close();
  return data;
}

void part1(std::vector<std::pair<std::string, std::string> >& data) {
  // 2, 4, 3, 7
  int cnt = 0;
  for (const auto& elem : data) {
    std::string signals = elem.second;
    std::stringstream ss(signals);
    std::string temp;
    while (ss.good()) {
      ss >> temp;
      if (temp.length() == 2 || temp.length() == 4 || temp.length() == 3 || temp.length() == 7) {
        cnt++;
      }
    }
  }
  std::cout << cnt << std::endl;
}

// std::set<char> one =    {          'c',           'f'     };
// std::set<char> seven =  {'a',      'c',           'f'     };
// std::set<char> four =   {     'b', 'c', 'd',      'f'     };
// std::set<char> two =    {'a',      'c', 'd', 'e',      'g'};
// std::set<char> five =   {'a', 'b',      'd',      'f', 'g'};
// std::set<char> three =  {'a',      'c', 'd',      'f', 'g'};
// std::set<char> zero =   {'a', 'b', 'c',      'e', 'f', 'g'};
// std::set<char> nine =   {'a', 'b', 'c', 'd',      'f', 'g'};
// std::set<char> six =    {'a', 'b',      'd', 'e', 'f', 'g'};
// std::set<char> eight =  {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....

//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg

void part2(std::vector<std::pair<std::string, std::string> >& data) {
}

int main(int argc, char** argv) {
  // std::vector<std::pair<std::string, std::string> > data = readInputs("day8_test.txt");
  std::vector<std::pair<std::string, std::string> > data = readInputs("day8_input.txt");
  part1(data);
  part2(data);
  return 0;
}