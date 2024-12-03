import 'dart:io';

void part1(List<String> lines) {
  int ret = 0;
  for (var line in lines) {
    List<int> nums = line.split(' ').map(int.parse).toList();
    int last = nums.last;

    List<int> diffs =
        List.generate(nums.length - 1, (i) => nums[i + 1] - nums[i]);

    while (diffs.toSet().length > 1) {
      last += diffs.last;
      diffs = List.generate(diffs.length - 1, (i) => diffs[i + 1] - diffs[i]);
    }

    ret += last + diffs.last;
  }
  print(ret);
}

void part2(List<String> lines) {
  int ret = 0;
  for (var line in lines) {
    List<int> nums = line.split(' ').reversed.map(int.parse).toList();
    int last = nums.last;

    List<int> diffs =
        List.generate(nums.length - 1, (i) => nums[i + 1] - nums[i]);

    while (diffs.toSet().length > 1) {
      last += diffs.last;
      diffs = List.generate(diffs.length - 1, (i) => diffs[i + 1] - diffs[i]);
    }

    ret += last + diffs.last;
  }
  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  part1(lines);
  part2(lines);
}
