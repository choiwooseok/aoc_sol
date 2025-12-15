#include <iostream>
#include <format>
#include <unordered_map>
#include <numeric>

#include "../util.h"

class Region {
 public:
  int width_;
  int height_;
  std::vector<int> quantities;
};

class Present {
 public:
  int count() const {
    return std::accumulate(shape_.begin(), shape_.end(), 0,
                           [](int acc, const auto& row) {
                             return acc + std::count(row.begin(), row.end(), '#');
                           });
  }

 public:
  std::vector<std::vector<char>> shape_;
};

auto _parse(const std::vector<std::string>& lines)
    -> std::tuple<std::vector<Present>, std::vector<Region>> {
  std::vector<Present> presents;
  std::vector<Region> regions;

  for (int i = 0; i < lines.size(); i++) {
    auto line = lines[i];
    if (line.empty()) continue;

    if (line.find(':') != std::string::npos) {
      if (line.find('x') != std::string::npos) {
        auto dim = split(line.substr(0, line.find(':')), "x");
        auto quantities = split(line.substr(line.find(':') + 2), " ");

        Region region;
        region.width_ = std::stoi(dim[0]);
        region.height_ = std::stoi(dim[1]);
        for (auto& q : quantities) region.quantities.push_back(std::stoi(q));
        regions.push_back(region);

      } else {
        Present present;
        for (int j = i + 1; j <= i + 3; j++) present.shape_.push_back(std::vector<char>(lines[j].begin(), lines[j].end()));
        presents.push_back(present);

        i += 3;
      }
    }
  }

  return {presents, regions};
}

uint64_t part1(const std::vector<std::string>& lines) {
  auto [presents, regions] = _parse(lines);
  int cnt = 0;
  for (const auto& region : regions) {
    auto area = region.width_ * region.height_;

    int acc = 0;
    for (int i = 0; i < 6; i++) {
      acc += region.quantities[i] * presents[i].count();
    }
    if (area >= acc) cnt++;
  }

  return cnt;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day12/input.txt");

  {
    auto [result, ms] = measure_ms(part1, lines);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}