#include <iostream>
#include <format>
#include <map>
#include <cmath>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "../util.h"

using Point = std::pair<int64_t, int64_t>;

struct PointHash {
  size_t operator()(const Point& p) const {
    return std::hash<int64_t>()(p.first) ^ (std::hash<int64_t>()(p.second) << 1);
  }
};

std::vector<Point> _parse(const std::vector<std::string>& lines) {
  std::vector<Point> points;
  for (auto& line : lines) {
    auto arr = split(line, ",");
    points.push_back({std::stoll(arr[0]), std::stoll(arr[1])});
  }
  return points;
}

uint64_t part1(const std::vector<std::string>& lines) {
  auto points = _parse(lines);

  uint64_t maxArea = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      auto [ix, iy] = points[i];
      auto [jx, jy] = points[j];

      uint64_t area = (std::llabs(ix - jx) + 1) * (std::llabs(iy - jy) + 1);
      maxArea = std::max(maxArea, area);
    }
  }
  return maxArea;
}

class PolygonChecker {
 public:
  PolygonChecker(const std::vector<Point>& points) : points_(points) {
    for (int i = 0; i < points_.size(); i++) {
      auto [x1, y1] = points_[i];
      auto [x2, y2] = points_[(i + 1) % points_.size()];

      if (y1 == y2) {
        int64_t minX = std::min(x1, x2);
        int64_t maxX = std::max(x1, x2);
        hSegments_[y1].push_back({minX, maxX});
      } else if (x1 == x2) {
        int64_t minY = std::min(y1, y2);
        int64_t maxY = std::max(y1, y2);
        vSegments_[x1].push_back({minY, maxY});
      }
    }
  }

  bool isOnBoundary(int64_t x, int64_t y) const {
    auto hIt = hSegments_.find(y);
    if (hIt != hSegments_.end()) {
      for (auto& [minX, maxX] : hIt->second) {
        if (x >= minX && x <= maxX) {
          return true;
        }
      }
    }

    auto vIt = vSegments_.find(x);
    if (vIt != vSegments_.end()) {
      for (auto& [minY, maxY] : vIt->second) {
        if (y >= minY && y <= maxY) {
          return true;
        }
      }
    }

    return false;
  }

  bool isInsidePolygon(int64_t x, int64_t y) const {
    Point p = {x, y};
    auto it = insideCache.find(p);
    if (it != insideCache.end()) {
      return it->second;
    }

    bool result = _isInsidePolygon(x, y);
    insideCache[p] = result;
    return result;
  }

  bool isValid(int64_t x, int64_t y) const {
    return isOnBoundary(x, y) || isInsidePolygon(x, y);
  }

 private:
  const std::vector<Point>& points_;
  std::unordered_map<int64_t, std::vector<std::pair<int64_t, int64_t>>> hSegments_;
  std::unordered_map<int64_t, std::vector<std::pair<int64_t, int64_t>>> vSegments_;

  mutable std::unordered_map<Point, bool, PointHash> insideCache;

  bool _isInsidePolygon(int64_t x, int64_t y) const {
    int n = points_.size();
    bool inside = false;

    for (int i = 0, j = n - 1; i < n; j = i++) {
      auto [ix, iy] = points_[i];
      auto [jx, jy] = points_[j];

      bool intersect = ((iy > y) != (jy > y)) && (x < (jx - ix) * (y - iy) / (jy - iy) + ix);
      if (intersect) inside = !inside;
    }

    return inside;
  }
};

uint64_t part2(const std::vector<std::string>& lines) {
  auto points = _parse(lines);
  PolygonChecker checker(points);

  std::unordered_set<Point, PointHash> validPoints;

  std::set<int64_t> xCoords, yCoords;
  for (auto& [x, y] : points) {
    xCoords.insert(x);
    yCoords.insert(y);
  }

  for (auto x : xCoords) {
    for (auto y : yCoords) {
      if (checker.isValid(x, y)) {
        validPoints.insert({x, y});
      }
    }
  }

  uint64_t maxArea = 0;

  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      auto [ix, iy] = points[i];
      auto [jx, jy] = points[j];

      int64_t x1 = std::min(ix, jx);
      int64_t y1 = std::min(iy, jy);
      int64_t x2 = std::max(ix, jx);
      int64_t y2 = std::max(iy, jy);

      if (!validPoints.count({x1, y1})) continue;
      if (!validPoints.count({x2, y1})) continue;
      if (!validPoints.count({x2, y2})) continue;
      if (!validPoints.count({x1, y2})) continue;

      bool valid = true;

      for (auto x : xCoords) {
        if (x < x1 || x > x2) continue;
        for (auto y : yCoords) {
          if (y < y1 || y > y2) continue;
          if (!validPoints.count({x, y})) {
            valid = false;
            break;
          }
        }
        if (!valid) break;
      }

      if (valid) {
        uint64_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
        maxArea = std::max(maxArea, area);
      }
    }
  }

  return maxArea;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day9/input.txt");

  {
    auto [result, ms] = measure_ms(part1, lines);
    std::cout << std::format("part1 : {}\n - elapsed : {} ms\n", result, ms);
  }

  {
    auto [result, ms] = measure_ms(part2, lines);
    std::cout << std::format("part2 : {}\n - elapsed : {} ms\n", result, ms);
  }

  return 0;
}