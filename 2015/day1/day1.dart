import 'dart:io';

void part1(String line) {
  int result = line.split('').fold(0, (sum, ch) => sum + (ch == '(' ? 1 : -1));
  print(result);
}

void part2(String line) {
  int pos = 0;
  for (int i = 0; i < line.length; i++) {
    pos += (line[i] == '(' ? 1 : -1);
    if (pos == -1) {
      print(i + 1);
      break;
    }
  }
}

void main() {
  String input = File('input.txt').readAsStringSync();
  part1(input);
  part2(input);
}
