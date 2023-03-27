#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

static std::string substringBefore(const std::string& str, const std::string& separator) {
  if (str.empty() || separator.empty()) {
    return str;
  }
  return str.find(separator) == std::string::npos ? str : str.substr(0, str.find(separator));
}

static std::string substringAfter(const std::string& str, const std::string& separator) {
  if (str.empty()) {
    return str;
  }
  if (separator.empty()) {
    return "";
  }
  return str.find(separator) == std::string::npos ? "" : str.substr(str.find(separator) + separator.length());
}

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

//             [G] [W]         [Q]
// [Z]         [Q] [M]     [J] [F]
// [V]         [V] [S] [F] [N] [R]
// [T]         [F] [C] [H] [F] [W] [P]
// [B] [L]     [L] [J] [C] [V] [D] [V]
// [J] [V] [F] [N] [T] [T] [C] [Z] [W]
// [G] [R] [Q] [H] [Q] [W] [Z] [G] [B]
// [R] [J] [S] [Z] [R] [S] [D] [L] [J]
//  1   2   3   4   5   6   7   8   9
std::vector<std::stack<char>> initialState() {
  std::vector<std::stack<char>> sts;
  {
    std::stack<char> st;
    st.push('R');
    st.push('G');
    st.push('J');
    st.push('B');
    st.push('T');
    st.push('V');
    st.push('Z');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('J');
    st.push('R');
    st.push('V');
    st.push('L');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('S');
    st.push('Q');
    st.push('F');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('Z');
    st.push('H');
    st.push('N');
    st.push('L');
    st.push('F');
    st.push('V');
    st.push('Q');
    st.push('G');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('R');
    st.push('Q');
    st.push('T');
    st.push('J');
    st.push('C');
    st.push('S');
    st.push('M');
    st.push('W');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('S');
    st.push('W');
    st.push('R');
    st.push('C');
    st.push('H');
    st.push('F');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('D');
    st.push('Z');
    st.push('C');
    st.push('V');
    st.push('F');
    st.push('N');
    st.push('J');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('L');
    st.push('G');
    st.push('Z');
    st.push('D');
    st.push('W');
    st.push('R');
    st.push('F');
    st.push('Q');
    sts.push_back(st);
  }

  {
    std::stack<char> st;
    st.push('J');
    st.push('B');
    st.push('W');
    st.push('V');
    st.push('P');
    sts.push_back(st);
  }

  return sts;
}

void part1(const std::vector<std::string>& data) {
  auto sts = initialState();
  for (auto line : data) {
    int popcnt = std::stoi(substringAfter(substringBefore(line, "from"), "move "));
    int from = std::stoi(substringBefore(substringAfter(line, "from "), "to")) - 1;
    int to = std::stoi(substringAfter(line, "to ")) - 1;

    for (int i = 0; i < popcnt; i++) {
      sts[to].push(sts[from].top());
      sts[from].pop();
    }
  }

  for (auto st : sts) {
    std::cout << st.top();
  }
  std::cout << std::endl;
}

void part2(const std::vector<std::string>& data) {
  auto sts = initialState();
  for (auto line : data) {
    int popcnt = std::stoi(substringAfter(substringBefore(line, "from"), "move "));
    int from = std::stoi(substringBefore(substringAfter(line, "from "), "to")) - 1;
    int to = std::stoi(substringAfter(line, "to ")) - 1;

    std::vector<int> move;
    for (int i = 0; i < popcnt; i++) {
      move.push_back(sts[from].top());
      sts[from].pop();
    }

    std::reverse(move.begin(), move.end());
    for (int elem : move) {
      sts[to].push(elem);
    }
  }

  for (auto st : sts) {
    std::cout << st.top();
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> data = readInputs("input.txt");
  part1(data);
  part2(data);
  return 0;
}