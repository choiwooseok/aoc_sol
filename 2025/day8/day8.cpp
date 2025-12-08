#include <iostream>
#include <format>
#include <map>
#include <cmath>
#include <array>
#include "../util.h"

using Point = std::array<int64_t, 3>;

int64_t _dist(const Point& l, const Point& r) {
  return std::sqrt((l[0] - r[0]) * (l[0] - r[0]) +
                   (l[1] - r[1]) * (l[1] - r[1]) +
                   (l[2] - r[2]) * (l[2] - r[2]));
}

std::vector<Point> _parse(const std::vector<std::string>& lines) {
  std::vector<Point> points;
  for (auto& line : lines) {
    auto arr = split(line, ",");
    points.push_back({std::stoll(arr[0]), std::stoll(arr[1]), std::stoll(arr[2])});
  }
  return points;
}

// from
// https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/
class UnionFind {
 public:
  UnionFind(int n) {
    parent_.resize(n);
    for (int i = 0; i < n; i++) {
      parent_[i] = i;
    }
    size_.resize(n, 1);
  }

  int find(int i) {
    int root = parent_[i];
    if (parent_[root] != root) {
      return parent_[i] = find(root);
    }
    return root;
  }

  void unionBySize(int i, int j) {
    int irep = find(i);
    int jrep = find(j);

    if (irep == jrep)
      return;

    int isize = size_[irep];
    int jsize = size_[jrep];
    if (isize < jsize) {
      parent_[irep] = jrep;
      size_[jrep] += size_[irep];
    } else {
      parent_[jrep] = irep;
      size_[irep] += size_[jrep];
    }
  }

  std::vector<int> getSize() { return size_; }

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
};

void _init_edges(const std::vector<Point>& points,
                 std::vector<std::pair<int64_t, std::pair<int, int>>>& edges) {
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      auto dist = _dist(points[i], points[j]);
      edges.push_back({dist, {i, j}});
    }
  }

  // sort : l.dist < r.dist
  std::sort(edges.begin(), edges.end());
}

uint64_t part1(const std::vector<std::string>& lines) {
  auto points = _parse(lines);

  // (dist, pair(idx, idx))
  std::vector<std::pair<int64_t, std::pair<int, int>>> edges;
  _init_edges(points, edges);

  UnionFind uf(points.size());
  for (int i = 0; i < 1000; i++) {
    auto [u, v] = edges[i].second;
    uf.unionBySize(u, v);
  }

  auto sizes = uf.getSize();
  std::sort(sizes.begin(), sizes.end(), std::greater<int>());
  return sizes[0] * sizes[1] * sizes[2];
}

uint64_t part2(const std::vector<std::string>& lines) {
  auto points = _parse(lines);

  std::vector<std::pair<int64_t, std::pair<int, int>>> edges;
  _init_edges(points, edges);

  UnionFind uf(points.size());

  uint64_t cnt = 0;
  for (int i = 0; i < edges.size(); i++) {
    auto [u, v] = edges[i].second;
    if (uf.find(u) != uf.find(v)) {
      uf.unionBySize(u, v);
      cnt++;

      if (cnt == points.size() - 1) {
        return points[u][0] * points[v][0];
      }
    }
  }

  return 0;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day8/input.txt");

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
