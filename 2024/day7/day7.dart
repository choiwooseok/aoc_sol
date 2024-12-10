import 'dart:io';

bool evaluate(List<int> nums, int target) {
  int n = nums.length;
  for (int i = 0; i < (1 << (n - 1)); i++) {
    int result = nums[0];
    for (int j = 0; j < n - 1; j++) {
      if ((i & (1 << j)) != 0) {
        result += nums[j + 1];
      } else {
        result *= nums[j + 1];
      }
    }
    if (result == target) return true;
  }
  return false;
}

bool _part2(List<int> nums, int target) {
  int n = nums.length;
  for (int i = 0; i < (1 << (2 * (n - 1))); i++) {
    int result = nums[0];
    for (int j = 0; j < n - 1; j++) {
      int op = (i >> (2 * j)) % 3;
      if (op == 0) {
        result += nums[j + 1];
      } else if (op == 1) {
        result *= nums[j + 1];
      } else if (op == 2) {
        result = int.parse(result.toString() + nums[j + 1].toString());
      }
    }
    if (result == target) return true;
  }
  return false;
}

void part1(List<String> lines) {
  int ret = 0;
  for (var line in lines) {
    List<int> nums =
        line.replaceAll(':', '').split(' ').map(int.parse).toList();
    int target = nums.removeAt(0);
    if (evaluate(nums, target)) {
      ret += target;
    }
  }
  print(ret);
}

void part2(List<String> lines) {
  int ret = 0;
  for (var line in lines) {
    List<int> nums =
        line.replaceAll(':', '').split(' ').map(int.parse).toList();
    int target = nums.removeAt(0);
    if (_part2(nums, target)) {
      ret += target;
    }
  }
  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  part1(lines);
  part2(lines);
}
