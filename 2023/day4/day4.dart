import 'dart:io';
import 'dart:math';

void part1(List<String> lines) {
  num ret = 0;
  for (int i = 0; i < lines.length; i++) {
    List<String> deck = lines[i].split(':').last.split('|');
    List<String> cards = deck[0].split(' ')..removeWhere((e) => e.isEmpty);
    List<String> nums = deck[1].split(' ')..removeWhere((e) => e.isEmpty);

    var win = cards.where((winning) => nums.contains(winning));
    ret += win.isNotEmpty ? pow(2, win.length - 1) : 0;
  }

  print(ret);
}

void part2(List<String> lines) {
  List<int> cnt = List.generate(lines.length, (index) => 1);

  for (int i = 0; i < lines.length; i++) {
    List<String> deck = lines[i].split(':').last.split('|');
    List<String> cards = deck[0].split(' ')..removeWhere((e) => e.isEmpty);
    List<String> nums = deck[1].split(' ')..removeWhere((e) => e.isEmpty);

    var win = cards.where((winning) => nums.contains(winning));
    for (int j = 0; j < win.length; j++) {
      cnt[j + i + 1] += cnt[i];
    }
  }

  print(cnt.fold<num>(0, (a, b) => a + b));
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');

  part1(lines);
  part2(lines);
}
