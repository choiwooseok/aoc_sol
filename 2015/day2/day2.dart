import 'dart:io';

void part1(List<String> lines) {
  num ret = 0;
  for (var line in lines) {
    List<int> dimensions = line.split('x').map((e) => int.parse(e)).toList()
      ..sort();

    var l = dimensions[0];
    var w = dimensions[1];
    var h = dimensions[2];

    ret += 3 * l * w + 2 * w * h + 2 * h * l;
  }
  print(ret);
}

void part2(List<String> lines) {
  num ret = 0;
  for (var line in lines) {
    List<int> dimensions = line.split('x').map((e) => int.parse(e)).toList()
      ..sort();

    var l = dimensions[0];
    var w = dimensions[1];
    var h = dimensions[2];

    ret += l * w * h + 2 * (l + w);
  }
  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  part1(lines);
  part2(lines);
}
