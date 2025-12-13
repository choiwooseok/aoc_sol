#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

#include "../util.h"

std::string _removeBraces(const std::string& str) {
  std::string ret = str;
  ret.pop_back();
  ret = ret.substr(1);
  return ret;
}

auto _parse(const std::vector<std::string>& lines) {
  std::vector<std::tuple<std::string, std::vector<std::string>, std::vector<int>>> tuples;

  for (auto& line : lines) {
    auto arr = split(line, " ");

    std::string light_diagram;
    std::vector<std::string> wiring_shematics;
    std::vector<int> joltage_requirements;

    for (auto& elem : arr) {
      if (elem.starts_with('[') && elem.ends_with(']')) {
        light_diagram = _removeBraces(elem);

      } else if (elem.starts_with('(') && elem.ends_with(')')) {
        std::string brace_removed = _removeBraces(elem);

        std::string wiring_shematic(light_diagram.size(), '0');

        auto inner = split(brace_removed, ",");
        for (auto& item : inner) {
          wiring_shematic[std::stoi(item)] = '1';
        }
        wiring_shematics.push_back(wiring_shematic);

      } else if (elem.starts_with('{') && elem.ends_with('}')) {
        std::string brace_removed = _removeBraces(elem);

        auto inner = split(brace_removed, ",");
        for (auto& item : inner) {
          joltage_requirements.push_back(std::stoi(item));
        }
      }
    }

    tuples.push_back({light_diagram, wiring_shematics, joltage_requirements});
  }
  return tuples;
}

int _backtrack(int current_state,
               int target_state,
               const std::vector<int>& button_masks,
               int button_idx,
               int current_presses,
               int& min_presses) {
  if (current_state == target_state) {
    min_presses = std::min(min_presses, current_presses);
    return current_presses;
  }

  if (button_idx >= button_masks.size() || current_presses >= min_presses) {
    return INT_MAX;
  }

  int result1 = _backtrack(current_state,
                           target_state,
                           button_masks,
                           button_idx + 1,
                           current_presses,
                           min_presses);

  int result2 = _backtrack(current_state ^ button_masks[button_idx],
                           target_state,
                           button_masks,
                           button_idx + 1,
                           current_presses + 1,
                           min_presses);

  return std::min(result1, result2);
}

uint64_t part1(const std::vector<std::string>& lines) {
  auto machines = _parse(lines);

  uint64_t total = 0;

  for (auto& [light_diagram, wiring_shematics, _] : machines) {
    int min_presses = INT_MAX;

    int target_mask = 0;
    for (int i = 0; i < light_diagram.size(); i++) {
      if (light_diagram[i] == '#') {
        target_mask |= (1 << i);
      }
    }

    std::vector<int> button_masks;
    for (auto& button : wiring_shematics) {
      int mask = 0;
      for (int i = 0; i < button.size(); i++) {
        if (button[i] == '1') {
          mask |= (1 << i);
        }
      }
      button_masks.push_back(mask);
    }

    int initial_state = 0;
    _backtrack(initial_state, target_mask, button_masks, 0, 0, min_presses);
    total += min_presses;
  }

  return total;
}

// ========== Part 2: Gaussian Elimination ==========

void scale(std::vector<int64_t>& v, int64_t s) {
  for (auto& val : v) {
    val *= s;
  }
}

bool is_zero_row(const std::vector<int64_t>& v) {
  return std::all_of(v.begin(), v.end(), [](int64_t x) { return x == 0; });
}

bool is_non_zero_row(const std::vector<int64_t>& v) {
  return !is_zero_row(v);
}

std::vector<int64_t> reduce(std::vector<int64_t> row_to_reduce,
                            std::vector<int64_t> reducing_row,
                            int64_t reducing_column) {
  if (row_to_reduce[reducing_column] == 0) {
    return row_to_reduce;
  }

  assert(reducing_row[reducing_column] > 0);
  if (row_to_reduce[reducing_column] < 0) {
    scale(row_to_reduce, -1);
  }

  int64_t scale_to = std::lcm(row_to_reduce[reducing_column], reducing_row[reducing_column]);
  scale(row_to_reduce, scale_to / row_to_reduce[reducing_column]);
  scale(reducing_row, scale_to / reducing_row[reducing_column]);

  for (size_t i = 0; i < row_to_reduce.size(); i++) {
    row_to_reduce[i] -= reducing_row[i];
  }

  return row_to_reduce;
}

void reduce_and_trim(std::vector<std::vector<int64_t>>& matrix) {
  int64_t diagonal_end = std::min<int64_t>(matrix.size(), matrix.front().size() - 1);

  for (int64_t diagonal = 0; diagonal < diagonal_end; diagonal++) {
    // 비어있지 않은 행을 위로
    std::partition(matrix.begin() + diagonal, matrix.end(), is_non_zero_row);

    // 현재 열에 0이 아닌 원소가 있는 행 찾기
    for (int64_t reducing_row = diagonal; reducing_row < (int64_t)matrix.size(); reducing_row++) {
      if (matrix[reducing_row][diagonal] != 0) {
        std::swap(matrix[diagonal], matrix[reducing_row]);
        break;
      }
    }

    if (matrix[diagonal][diagonal] < 0) {
      scale(matrix[diagonal], -1);
    }

    // 아래 행들 소거
    for (int64_t row_to_reduce = diagonal + 1; row_to_reduce < (int64_t)matrix.size(); row_to_reduce++) {
      matrix[row_to_reduce] = reduce(matrix[row_to_reduce], matrix[diagonal], diagonal);
    }
  }

  // 0인 행 제거
  matrix.erase(std::remove_if(matrix.begin(), matrix.end(), is_zero_row), matrix.end());
}

void try_solve_constrained(const std::vector<std::vector<int8_t>>& buttons,
                           const std::vector<int16_t>& targets,
                           const std::vector<std::vector<int64_t>>& matrix,
                           int64_t row_to_solve,
                           int64_t next_unknown,
                           const std::vector<int64_t>& constraints,
                           std::vector<int64_t>& solution,
                           int64_t& minimum_presses) {
  // 모든 버튼을 결정했으면 검증
  if (next_unknown == -1) {
    std::vector<int16_t> accumulated(targets.size(), 0);
    for (size_t button = 0; button < buttons.size(); button++) {
      for (int8_t counter : buttons[button]) {
        accumulated[counter] += (int16_t)solution[button];
      }
    }

    if (accumulated == targets) {
      minimum_presses = std::min(minimum_presses,
                                 std::accumulate(solution.begin(), solution.end(), 0LL));
    }
    return;
  }

  // 행렬이 부족하면 추측
  if (next_unknown > row_to_solve) {
    for (int64_t guess = 0; guess <= constraints[next_unknown]; guess++) {
      solution[next_unknown] = guess;
      try_solve_constrained(buttons, targets, matrix, row_to_solve, next_unknown - 1,
                            constraints, solution, minimum_presses);
    }
    return;
  }

  assert(row_to_solve == next_unknown);

  // 대각선 원소가 0이면 추측
  if (matrix[row_to_solve][next_unknown] == 0) {
    for (int64_t guess = 0; guess <= constraints[next_unknown]; guess++) {
      solution[next_unknown] = guess;
      try_solve_constrained(buttons, targets, matrix, row_to_solve - 1, next_unknown - 1,
                            constraints, solution, minimum_presses);
    }
    return;
  }

  // 직접 계산 가능
  int64_t row_target_sum = matrix[row_to_solve].back();

  // 이미 알고 있는 버튼들의 기여 제거
  for (int64_t known = next_unknown + 1; known < (int64_t)solution.size(); known++) {
    row_target_sum -= matrix[row_to_solve][known] * solution[known];
  }

  // 정수 해가 존재하는지 확인
  if ((row_target_sum % matrix[row_to_solve][next_unknown]) != 0) {
    return;  // 유효하지 않은 해
  }

  int64_t tentative_solution = row_target_sum / matrix[row_to_solve][next_unknown];
  if (tentative_solution < 0) {
    return;  // 양수 해만 찾음
  }

  solution[next_unknown] = tentative_solution;

  try_solve_constrained(buttons, targets, matrix, row_to_solve - 1, next_unknown - 1,
                        constraints, solution, minimum_presses);
}

int64_t _part2(const std::vector<std::string>& buttons_str,
               const std::vector<int>& targets_int) {
  int n = targets_int.size();
  int m = buttons_str.size();

  // 데이터 타입 변환
  std::vector<int16_t> targets(targets_int.begin(), targets_int.end());
  std::vector<std::vector<int8_t>> buttons;

  for (const auto& button_str : buttons_str) {
    std::vector<int8_t> button;
    for (int i = 0; i < n; i++) {
      if (button_str[i] == '1') {
        button.push_back(i);
      }
    }
    buttons.push_back(button);
  }

  // Augmented matrix 생성
  std::vector<std::vector<int64_t>> matrix(n, std::vector<int64_t>(m + 1, 0));

  for (int col = 0; col < m; col++) {
    for (int8_t row : buttons[col]) {
      matrix[row][col] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    matrix[i].back() = targets[i];
  }

  // Constraints 계산
  std::vector<int64_t> constraints(m, INT64_MAX);
  for (int button = 0; button < m; button++) {
    for (int8_t counter : buttons[button]) {
      constraints[button] = std::min<int64_t>(constraints[button], targets[counter]);
    }
  }

  // 가우스 소거
  reduce_and_trim(matrix);

  // 백트래킹으로 해 찾기
  std::vector<int64_t> solution(m, -1);
  int64_t minimum_presses = INT64_MAX;

  try_solve_constrained(buttons, targets, matrix,
                        std::min<int64_t>(m - 1, matrix.size() - 1),
                        m - 1, constraints, solution, minimum_presses);

  return minimum_presses;
}

uint64_t part2(const std::vector<std::string>& lines) {
  auto machines = _parse(lines);
  uint64_t total = 0;

  for (auto& [_, wiring_shematics, joltage_requirements] : machines) {
    total += _part2(wiring_shematics, joltage_requirements);
  }

  return total;
}

int main(int argc, char** argv) {
  auto lines = read_lines("day10/input.txt");

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