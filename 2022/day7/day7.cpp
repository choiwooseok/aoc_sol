#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> split(const std::string& source, const std::string& delim) {
  size_t pos_start = 0, pos_end, delim_len = delim.length();
  std::vector<std::string> res;

  while ((pos_end = source.find(delim, pos_start)) != std::string::npos) {
    std::string token = source.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(source.substr(pos_start));
  return res;
}

bool starts_with(const std::string& src, const std::string& starting) {
  return src.length() >= starting.length() ? (0 == src.compare(0, starting.length(), starting)) : false;
}

class File {
 public:
  File(const std::string& name, int64_t size) : name(name), size(size) {}
  std::string name;
  int64_t size;
};

class Node {
 public:
  Node(const std::string& name, std::shared_ptr<Node> parent) : name(name), parent(parent) {}

  void addFile(const std::string& name, int64_t size) {
    files.emplace_back(name, size);
  }

  void addChild(std::shared_ptr<Node> child) {
    childs.push_back(child);
  }

  std::vector<std::shared_ptr<Node>> childs;
  std::shared_ptr<Node> parent;
  std::vector<File> files;

  std::string name;
  int64_t size{0};
};

std::vector<std::string> readInputs(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::string> data;

  std::string line;
  while (!inputs.eof()) {
    std::getline(inputs, line);
    data.push_back(line);
  }
  inputs.close();
  return data;
}

int64_t init_size(std::shared_ptr<Node> node) {
  int64_t sum = 0;
  for (auto file : node->files) {
    sum += file.size;
  }
  node->size = sum;
  if (node->childs.empty()) {
    return node->size;
  }
  for (auto child : node->childs) {
    node->size += init_size(child);
  }
  return node->size;
}

std::shared_ptr<Node> init_node(const std::vector<std::string>& data) {
  std::shared_ptr<Node> curr = std::make_shared<Node>("/", nullptr);

  for (auto& line : data) {
    if (starts_with(line, "$")) {
      auto cmds = split(line.substr(2), " ");
      if (starts_with(cmds[0], "cd")) {
        if (cmds[1] == "/") {
        } else if (cmds[1] == "..") {
          curr = curr->parent;
        } else {
          auto dir = std::make_shared<Node>(cmds[1], curr);
          curr->addChild(dir);
          curr = dir;
        }
      }
    } else if (starts_with(line, "dir")) {
    } else {
      auto cmds = split(line, " ");
      curr->addFile(cmds[1], std::stoll(cmds[0]));
    }
  }

  while (curr->name != "/") {
    curr = curr->parent;
  }

  init_size(curr);

  return curr;
}

void part1_helper(std::shared_ptr<Node> node, int64_t& sum) {
  if (node->size <= 100000) {
    sum += node->size;
  }

  for (auto child : node->childs) {
    part1_helper(child, sum);
  }
}

void part1(const std::vector<std::string>& data) {
  auto root = init_node(data);
  int64_t sum = 0;
  part1_helper(root, sum);
  std::cout << sum << std::endl;
}

void part2_helper(std::shared_ptr<Node> node, std::vector<int64_t>& possible, int64_t need) {
  if (node->size >= need) {
    possible.push_back(node->size);
  }

  for (auto child : node->childs) {
    part2_helper(child, possible, need);
  }
}

void part2(const std::vector<std::string>& data) {
  auto root = init_node(data);
  std::vector<int64_t> possible;
  part2_helper(root, possible, root->size - 40000000);
  std::cout << *std::min_element(possible.begin(), possible.end()) << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readInputs("input.txt");
  part1(data);
  part2(data);
  return 0;
}