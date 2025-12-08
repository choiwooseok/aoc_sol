String _lookAndSay(String input) {
  if (input.isEmpty) return '';
  String result = '';
  int count = 1;
  String currentDigit = input[0];

  for (int i = 1; i < input.length; i++) {
    if (input[i] == currentDigit) {
      count++;
    } else {
      result += '$count$currentDigit';
      currentDigit = input[i];
      count = 1;
    }
  }
  result += '$count$currentDigit';
  return result;
}

int part1(int iterations, String start) {
  String curr = start;
  for (int i = 0; i < iterations; i++) {
    curr = _lookAndSay(curr);
  }

  return curr.length;
}

int part2(int iterations, String initialInput) {
  List<int> sequence = initialInput.codeUnits.toList();

  for (int i = 0; i < iterations; i++) {
    List<int> nextSequence = [];
    int j = 0;
    while (j < sequence.length) {
      int count = 1;
      int currentDigit = sequence[j];
      while (j + 1 < sequence.length && sequence[j + 1] == currentDigit) {
        count++;
        j++;
      }
      nextSequence.addAll(count.toString().codeUnits);
      nextSequence.add(currentDigit);
      j++;
    }
    sequence = nextSequence;
  }

  return sequence.length;
}

void main() {
  // print(part1(40, '3113322113'));
  print(part2(50, '3113322113'));
}
