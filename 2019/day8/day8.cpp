#include <iostream>
#include <algorithm>

#include "../util.h"

int part1(const std::string& input) {
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
  return std::count(minLayer.begin(), minLayer.end(), '1') * std::count(minLayer.begin(), minLayer.end(), '2');
}

void _print(const std::vector<char>& image, int width, int height) {
  for (size_t i = 0; i < width * height; i++) {
    std::cout << (image[i] == '1' ? '@' : ' ');
    if (i % width == width - 1) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

std::vector<char> part2(const std::string& input, int width, int height) {
  int layerSize = width * height;
  int layers = static_cast<int>(input.size()) / layerSize;
  std::vector<char> image(layerSize, '2');

  for (int p = 0; p < layerSize; ++p) {
    for (int l = 0; l < layers; ++l) {
      char ch = input[l * layerSize + p];
      if (ch == '0' || ch == '1') {
        image[p] = ch;
        break;
      }
      // if ch == '2' continue to next layer
    }
  }

  return image;
}

int main(int argc, char** argv) {
  auto line = read_line("day8/input.txt");

  {
    auto [result, ms] = measure_ms(part1, line);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, line, 25, 6);
    _print(result, 25, 6);
    std::cout << std::format("- elapsed : {} ms\n", ms);
  }

  return 0;
}
