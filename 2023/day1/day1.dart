import 'dart:io';

int part1(List<String> lines) {
  int sum = 0;
  for (var line in lines) {
    var digits = line.split('').where((c) => int.tryParse(c) != null).toList();
    if (digits.isNotEmpty) {
      int num = int.parse(digits.first + digits.last);
      sum += num;
    }
  }
  return sum;
}

int part2(List<String> lines) {
  Map<String, String> words = {
    'one': '1',
    'two': '2',
    'three': '3',
    'four': '4',
    'five': '5',
    'six': '6',
    'seven': '7',
    'eight': '8',
    'nine': '9',
  };

  int sum = 0;
  for (var line in lines) {
    int first = -1;
    int last = -1;

    // Find first
    for (int i = 0; i < line.length; i++) {
      if (int.tryParse(line[i]) != null) {
        first = int.parse(line[i]);
        break;
      }
      for (var word in words.keys) {
        if (i + word.length <= line.length &&
            line.substring(i, i + word.length) == word) {
          first = int.parse(words[word]!);
          break;
        }
      }
      if (first != -1) break;
    }

    // Find last
    for (int i = line.length - 1; i >= 0; i--) {
      if (int.tryParse(line[i]) != null) {
        last = int.parse(line[i]);
        break;
      }
      for (var word in words.keys) {
        if (i + word.length <= line.length &&
            line.substring(i, i + word.length) == word) {
          last = int.parse(words[word]!);
          break;
        }
      }
      if (last != -1) break;
    }

    if (first != -1 && last != -1) {
      int num = first * 10 + last;
      sum += num;
    }
  }
  return sum;
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input
      .split('\n')
      .where((line) => line.isNotEmpty)
      .toList();

  print('Part 1: ${part1(lines)}');
  print('Part 2: ${part2(lines)}');
}
