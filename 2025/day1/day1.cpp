#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::string> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> lines;
  std::string curr;
  while (std::getline(fs, curr)) lines.push_back(curr);
  fs.close();
  return lines;
}

enum class Direction {
  LEFT,
  RIGHT,
};

Direction getDir(char c) {
  return c == 'L' ? Direction::LEFT : Direction::RIGHT;
}

int normalize(int x, int mod) {
  int r = x % mod;
  if (r < 0) r += mod;
  return r;
}

int rotate(int start, Direction dir, int distance) {
  int step = normalize(distance, 100);
  switch (dir) {
    case Direction::LEFT:
      return normalize(start - step, 100);

    case Direction::RIGHT:
      return normalize(start + step, 100);
  }
}

// part1: count times the dial is left pointing at 0 after each rotation
int part1(int start, const std::vector<std::string>& instructions) {
  int pos = start;
  int count = 0;
  for (const auto& ins : instructions) {
    pos = rotate(pos, getDir(ins[0]), std::stoll(ins.substr(1)));
    if (pos == 0) count++;
  }
  return count;
}

// part2: count times the dial points at 0 during any click
int part2(int start, const std::vector<std::string>& instructions) {
  int pos = start;
  int count = 0;
  for (const auto& ins : instructions) {
    Direction dir = getDir(ins[0]);
    int dist = std::stoi(ins.substr(1));

    int t0 = (dir == Direction::RIGHT) ? ((100 - pos) % 100)
                                       : (pos % 100);
    if (t0 == 0) t0 = 100;

    if (dist >= t0) {
      count += 1 + (dist - t0) / 100;
    }

    pos = rotate(pos, dir, dist);
  }
  return count;
}

int main(int argc, char** argv) {
  auto instructions = read_lines("input.txt");
  std::cout << "part1 : " << part1(50, instructions) << std::endl;
  std::cout << "part2 : " << part2(50, instructions) << std::endl;
  return 0;
}
