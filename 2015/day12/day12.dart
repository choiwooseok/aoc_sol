import 'dart:convert';
import 'dart:io';

void part1(List<String> lines) {
  int sum = 0;
  for (var line in lines) {
    RegExp('(-?\\d+)').allMatches(line).forEach((match) {
      sum += int.parse(match.group(0) ?? '0');
    });
  }
  print(sum);
}

void part2(List<String> lines) {
  int sum(dynamic obj) {
    if (obj is int) {
      return obj;
    } else if (obj is List) {
      return obj.fold(0, (acc, e) => acc + sum(e));
    } else if (obj is Map) {
      if (obj.values.contains('red')) {
        return 0;
      }
      return obj.values.fold(0, (acc, e) => acc + sum(e));
    }
    return 0;
  }

  print(sum(jsonDecode(lines[0])));
}

void main() {
  String input = File('input.txt').readAsStringSync();
  part1(input.split('\n'));
  part2(input.split('\n'));
}
