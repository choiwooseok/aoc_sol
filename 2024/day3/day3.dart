import 'dart:io';

void part1(List<String> lines) {
  int ret = lines.fold(0, (sum, line) {
    return sum +
        RegExp(r"mul\((\d{1,3}),(\d{1,3})\)").allMatches(line).fold(0,
            (subSum, match) {
          int a = int.parse(match.group(1)!);
          int b = int.parse(match.group(2)!);
          return subSum + (a * b);
        });
  });
  print(ret);
}

void part2(List<String> lines) {
  bool isEnabled = true;
  int ret = 0;

  for (var line in lines) {
    for (var match in RegExp(r"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))")
        .allMatches(line)) {
      String instruction = match.group(0)!;

      if (instruction == "do()") {
        isEnabled = true;
      } else if (instruction == "don't()") {
        isEnabled = false;
      } else if (instruction.startsWith("mul") && isEnabled) {
        int a = int.parse(match.group(2)!);
        int b = int.parse(match.group(3)!);
        ret += a * b;
      }
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
