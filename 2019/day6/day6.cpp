#include <iostream>
#include <map>
#include <set>
#include <format>
#include <queue>

#include "../util.h"

std::map<std::string, std::vector<std::string>> build_graph(const std::vector<std::string>& lines) {
  std::map<std::string, std::vector<std::string>> graph;
  for (const auto& line : lines) {
    int idx = line.find(')');
    std::string parent = line.substr(0, idx);
    std::string child = line.substr(idx + 1);
    graph[parent].push_back(child);
    graph[child].push_back(parent);  // 양방향
  }
  return graph;
}

// BFS로 각 노드의 깊이 계산 (COM에서부터)
int part1(const std::vector<std::string>& lines) {
  auto graph = build_graph(lines);

  std::queue<std::pair<std::string, int>> q;
  std::set<std::string> visited;
  int total_orbits = 0;

  q.push({"COM", 0});
  visited.insert("COM");

  while (!q.empty()) {
    auto [current, depth] = q.front();
    q.pop();

    total_orbits += depth;

    for (const auto& neighbor : graph.at(current)) {
      if (visited.find(neighbor) == visited.end()) {
        visited.insert(neighbor);
        q.push({neighbor, depth + 1});
      }
    }
  }

  return total_orbits;
}

// BFS
int part2(const std::vector<std::string>& lines) {
  auto graph = build_graph(lines);

  // BFS: YOU가 궤도하는 객체에서 시작, SAN이 궤도하는 객체에 도달할 때까지
  std::string start_node;
  std::string end_node;

  for (const auto& [node, neighbors] : graph) {
    for (const auto& neighbor : neighbors) {
      if (neighbor == "YOU") start_node = node;
      if (neighbor == "SAN") end_node = node;
    }
  }

  std::queue<std::pair<std::string, int>> q;
  std::set<std::string> visited;

  q.push({start_node, 0});
  visited.insert(start_node);

  while (!q.empty()) {
    auto [current, distance] = q.front();
    q.pop();

    if (current == end_node) {
      return distance;
    }

    for (const auto& neighbor : graph.at(current)) {
      if (visited.find(neighbor) == visited.end()) {
        visited.insert(neighbor);
        q.push({neighbor, distance + 1});
      }
    }
  }

  return -1;  // 경로 없음
}

int main(int argc, char** argv) {
  auto lines = read_lines("day6/input.txt");

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