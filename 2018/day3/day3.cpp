#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Claim {
 public:
  std::string id;
  int x;
  int y;
  int w;
  int h;
};

std::vector<Claim> read_lines(const std::string& fileName) {
  std::fstream fs(fileName);
  std::vector<Claim> ret;

  std::string line;
  while (std::getline(fs, line)) {
    Claim c;
    c.id = line.substr(1, line.find('@') - 1);
    c.x = std::stoi(line.substr(line.find('@') + 1, line.find(',')));
    c.y = std::stoi(line.substr(line.find(',') + 1, line.find(':')));

    c.w = std::stoi(line.substr(line.find(':') + 1, line.find('x')));
    c.h = std::stoi(line.substr(line.find('x') + 1));
    ret.push_back(c);
  }

  fs.close();
  return ret;
}

void _apply(std::vector<std::vector<std::string>>& grid, const std::vector<Claim>& claims) {
  for (const auto& c : claims) {
    for (int i = c.y; i < c.y + c.h; i++) {
      for (int j = c.x; j < c.x + c.w; j++) {
        if (grid[i][j] == ".") {
          grid[i][j] = c.id;
        } else {
          grid[i][j] = "X";
        }
      }
    }
  }
}

int part1(const std::vector<Claim>& claims) {
  std::vector<std::vector<std::string>> grid(1000, std::vector<std::string>(1000, "."));

  _apply(grid, claims);

  int cnt = 0;
  for (auto& row : grid) {
    for (auto& col : row) {
      if (col == "X") {
        cnt++;
      }
    }
  }
  return cnt;
}

std::string part2(const std::vector<Claim>& claims) {
  std::vector<std::vector<std::string>> grid(1000, std::vector<std::string>(1000, "."));

  _apply(grid, claims);

  for (const auto& c : claims) {
    int cnt = 0;
    for (int i = c.y; i < c.y + c.h; i++) {
      for (int j = c.x; j < c.x + c.w; j++) {
        if (grid[i][j] == "X") break;
        if (grid[i][j] == c.id) {
          cnt++;
        }
      }
    }
    if (cnt == c.w * c.h) {
      return c.id;
    }
  }

  return "";
}

int main(int argc, char** argv) {
  auto claims = read_lines("input.txt");
  std::cout << "part1 : " << part1(claims) << std::endl;
  std::cout << "part2 : " << part2(claims) << std::endl;
  return 0;
}
