import 'dart:io';

bool _hasTwice(String str) {
  for (int i = 0; i < str.length - 1; i++) {
    if (str[i] == str[i + 1]) return true;
  }
  return false;
}

bool _hasBlackList(String str, List<String> blackList) {
  for (var item in blackList) {
    if (str.contains(item)) return true;
  }
  return false;
}

bool _hasThreeVowels(String str) {
  int cnt = 0;
  for (int i = 0; i < str.length; i++) {
    if ('aeiou'.contains(str[i])) cnt++;
  }
  return cnt >= 3;
}

bool _hasNonOverlappingPair(String s) {
  for (int i = 0; i < s.length - 1; i++) {
    String pair = s.substring(i, i + 2);
    if (s.indexOf(pair, i + 2) != -1) return true;
  }
  return false;
}

bool _hasSandwichLetter(String s) {
  for (int i = 0; i < s.length - 2; i++) {
    if (s[i] == s[i + 2]) return true;
  }
  return false;
}

int part1(List<String> lines) {
  int cnt = 0;
  for (var line in lines) {
    if (!_hasThreeVowels(line)) continue;
    if (!_hasTwice(line)) continue;
    if (_hasBlackList(line, ["ab", "cd", "pq", "xy"])) continue;
    cnt++;
  }
  return cnt;
}

int part2(List<String> lines) {
  int cnt = 0;
  for (var line in lines) {
    if (_hasNonOverlappingPair(line) && _hasSandwichLetter(line)) cnt++;
  }
  return cnt;
}

void main() {
  List<String> lines = File('input.txt').readAsStringSync().split('\n');
  print(part1(lines));
  print(part2(lines));
}
