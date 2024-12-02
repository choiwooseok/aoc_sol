import 'dart:io';

bool isIncOrDec(List<int> diffs) {
  return diffs.every((element) => element > 0) ||
      diffs.every((element) => element < 0);
}

bool isInRange(List<int> diffs) {
  return diffs.every((element) => 1 <= element.abs() && element.abs() <= 3);
}

void part1(List<String> lines) {
  print(lines.where((line) {
    List<int> levels = line.split(' ').map(int.parse).toList();
    List<int> diffs =
        List.generate(levels.length - 1, (i) => levels[i] - levels[i + 1]);
    return isIncOrDec(diffs) && isInRange(diffs);
  }).length);
}

void part2(List<String> lines) {
  int ret = 0;
  for (var line in lines) {
    List<int> levels = line.split(' ').map(int.parse).toList();
    for (int i = 0; i < levels.length; i++) {
      List<int> modifiedLevels = List.from(levels)..removeAt(i);
      List<int> diffs = List.generate(modifiedLevels.length - 1,
          (i) => modifiedLevels[i] - modifiedLevels[i + 1]);

      if (isIncOrDec(diffs) && isInRange(diffs)) {
        ret++;
        break;
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
