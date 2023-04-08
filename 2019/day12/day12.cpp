#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

static std::vector<std::string> split(const std::string& source, const std::string& delim) {
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

static std::string trim_right(const std::string& source, const std::string& whitespaces) {
  std::string str(source);
  return str.erase(str.find_last_not_of(whitespaces) + 1);
}

static std::string trim_left(const std::string& source, const std::string& whitespaces) {
  std::string str(source);
  return str.erase(0, str.find_first_not_of(whitespaces));
}

static std::string trim(const std::string& source, const std::string& whitespaces) {
  std::string str(source);
  return trim_left(trim_right(str, whitespaces), whitespaces);
}

static std::string strip(const std::string& source) {
  std::string str(source);
  return trim(trim(trim(trim(str, " "), "\t"), "\r"), "\n");
}

template <typename T>
void printVector(std::vector<T>& arr) {
  for (auto& elem : arr) {
    std::cout << elem << " ";
  }
}

int cmp(int a, int b) {
  if (a == b) {
    return 0;
  }
  if (a < b) {
    return 1;
  } else if (a > b) {
    return -1;
  }
}

void updateVel(std::vector<std::pair<std::vector<int>, std::vector<int> > >& pv_pairs) {
  for (int i = 0; i < 3; i++) {  // update vel
    int p0 = pv_pairs[0].first[i];
    int p1 = pv_pairs[1].first[i];
    int p2 = pv_pairs[2].first[i];
    int p3 = pv_pairs[3].first[i];

    pv_pairs[0].second[i] += cmp(p0, p1) + cmp(p0, p2) + cmp(p0, p3);
    pv_pairs[1].second[i] += cmp(p1, p0) + cmp(p1, p2) + cmp(p1, p3);
    pv_pairs[2].second[i] += cmp(p2, p0) + cmp(p2, p1) + cmp(p2, p3);
    pv_pairs[3].second[i] += cmp(p3, p0) + cmp(p3, p1) + cmp(p3, p2);
  }
}

void updatePos(std::vector<std::pair<std::vector<int>, std::vector<int> > >& pv_pairs) {
  for (auto& elem : pv_pairs) {  // update pos
    for (int i = 0; i < 3; i++) {
      elem.first[i] += elem.second[i];
    }
  }
}

bool check(std::vector<std::pair<std::vector<int>, std::vector<int> > >& pv_pairs) {
  std::vector<int> a = {5, -1, 5};
  std::vector<int> b = {0, -14, 2};
  std::vector<int> c = {16, 4, 0};
  std::vector<int> d = {18, 1, 16};
  std::vector<int> e = {0, 0, 0};
  for (auto& elem : pv_pairs) {
    if (elem.second != e) {
      return false;
    }
  }
  return pv_pairs[0].first == a && pv_pairs[1].first == b && pv_pairs[2].first == c && pv_pairs[3].first == d;
}

void step(std::vector<std::pair<std::vector<int>, std::vector<int> > >& pv_pairs) {
  updateVel(pv_pairs);
  updatePos(pv_pairs);
}

int main(int argc, char** argv) {
  //     std::string input = R"(<x=-1, y=0, z=2>
  // <x=2, y=-10, z=-7>
  // <x=4, y=-8, z=8>
  // <x=3, y=5, z=-1>)";

  //     std::string input = R"(<x=-8, y=-10, z=0>
  // <x=5, y=5, z=10>
  // <x=2, y=-7, z=3>
  // <x=9, y=-8, z=-3>)";

  std::string input = R"(<x=5, y=-1, z=5>
<x=0, y=-14, z=2>
<x=16, y=4, z=0>
<x=18, y=1, z=16>)";
  long long steps = 100000000000;

  std::stringstream ss(input);
  std::string line;
  std::vector<std::pair<std::vector<int>, std::vector<int> > > initial;
  while (std::getline(ss, line)) {
    line = line.substr(1);  // remove <
    line.pop_back();        // remove >
    std::vector<std::string> xyz = split(strip(line), ", ");
    std::vector<int> pos;
    for (int i = 0; i < 3; i++) {
      pos.push_back(std::stoi(xyz[i].substr(xyz[i].find("=") + 1)));
    }
    initial.push_back({pos, {0, 0, 0}});
  }

  for (long long i = 0; i < steps; i++) {
    step(initial);
    // std::cout << "After steps " << i + 1 << " : " << std::endl;
    // for(auto& elem : initial) {
    //     std::cout << "pos = ";
    //     printVector(elem.first);
    //     std::cout << "vel = ";
    //     printVector(elem.second);
    //     std::cout << std::endl;
    // }
    if (check(initial)) {
      std::cout << i << std::endl;
      break;
    }
  }

  // int sum = 0;
  // for(auto& pv : initial) {
  //     for(auto& elem : pv.first) {
  //         if(elem < 0) {
  //             elem = std::abs(elem);
  //         }
  //     }
  //     for(auto& elem : pv.second) {
  //         if(elem < 0) {
  //             elem = std::abs(elem);
  //         }
  //     }

  //     sum += std::accumulate(pv.first.begin(), pv.first.end(), 0) * std::accumulate(pv.second.begin(), pv.second.end(), 0);
  // }

  // std::cout << sum << std::endl;

  return 0;
}