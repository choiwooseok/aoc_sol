#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void part1() {
  std::ifstream in("input.txt");
  std::string input;
  in >> input;
  int width = 25;
  int height = 6;
  int layerSize = input.length() / width / height;

  std::vector<std::pair<std::string, int>> counts;
  for (int i = 0; i < layerSize; i++) {
    std::string layer = input.substr(width * height * i, width * height);
    counts.push_back({layer, std::count(layer.begin(), layer.end(), '0')});
  }

  std::sort(counts.begin(), counts.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
    return a.second < b.second;
  });

  std::string minLayer = counts.front().first;
  std::cout << std::count(minLayer.begin(), minLayer.end(), '1') * std::count(minLayer.begin(), minLayer.end(), '2') << std::endl;
}

void part2() {
  int width = 25;
  int height = 6;
  std::vector<char> image(width * height, '2');
  std::vector<char> layer(width * height);
  std::ifstream in("input.txt");
  char ch;
  if (in.is_open()) {
    while (in.good() && !in.eof()) {
      for (int i = 0; i < width * height; i++) {
        in >> ch;
        switch (ch) {
          case '0':
            layer[i] = ch;
            break;
          case '1':
            layer[i] = ch;
            break;
          case '2':
            layer[i] = ch;
            break;
          default:
            break;
        }
        if (image[i] == '2') {
          image[i] = layer[i];
        }
      }
    }
    for (size_t i = 0; i < width * height; i++) {
      std::cout << (image[i] == '1' ? '@' : ' ');
      if (i % width == width - 1) {
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv) {
  part1();

  part2();
  return 0;
}