import 'dart:io';

void part1(List<String> lines) {
  var left = lines.map((line) => int.parse(line.split('   ')[0])).toList()
    ..sort();
  var right = lines.map((line) => int.parse(line.split('   ')[1])).toList()
    ..sort();

  var ret = left
      .asMap()
      .entries
      .map((e) => (e.value - right[e.key]).abs())
      .reduce((a, b) => a + b);

  print(ret);
}

void part2(List<String> lines) {
  var left = lines.map((line) => int.parse(line.split('   ')[0])).toList();
  var right = lines.map((line) => int.parse(line.split('   ')[1])).toList();

  var ret = left
      .asMap()
      .entries
      .map((e) => (e.value * right.where((r) => r == e.value).length))
      .reduce((a, b) => a + b);

  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  part1(lines);
  part2(lines);
}
