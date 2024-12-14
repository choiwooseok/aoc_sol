import 'dart:io';

bool isEvenDigit(int n) => n.toString().length % 2 == 0;
bool isZero(int n) => n == 0;

// void part1(List<String> lines, int iter) {
//   for (var line in lines) {
//     List<int> nums = line.split(' ').map(int.parse).toList();

//     for (int i = 0; i < iter; i++) {
//       for (int j = 0; j < nums.length; j++) {
//         if (isZero(nums[j])) {
//           nums[j] = 1;
//         } else if (isEvenDigit(nums[j])) {
//           var numStr = nums[j].toString();
//           nums[j] = int.parse(numStr.substring(0, numStr.length ~/ 2));
//           nums.insert(j + 1, int.parse(numStr.substring(numStr.length ~/ 2)));
//           j++;
//         } else {
//           nums[j] *= 2024;
//         }
//       }
//       print('$i / $iter : ${nums.length}');
//     }
//   }
// }

int recur(Map<String, int> cache, int value, int depth) {
  String key = '$value|$depth';
  if (cache.containsKey(key)) {
    return cache[key]!;
  }

  int result;
  if (depth == 0) {
    result = 1;
  } else if (isZero(value)) {
    result = recur(cache, 1, depth - 1);
  } else {
    int digitCount = value.toString().length;
    if (isEvenDigit(value)) {
      int divisor = int.parse('1' + '0' * (digitCount ~/ 2));
      result = recur(cache, value ~/ divisor, depth - 1) +
          recur(cache, value % divisor, depth - 1);
    } else {
      result = recur(cache, value * 2024, depth - 1);
    }
  }

  cache[key] = result;
  return result;
}

int blinkRecurMemo(List<int> input, int count) {
  Map<String, int> cache = {};
  return input.map((v) => recur(cache, v, count)).reduce((a, b) => a + b);
}

void part2(List<String> lines, int iter) {
  List<int> nums =
      lines.expand((line) => line.split(' ').map(int.parse)).toList();
  int totalLength = blinkRecurMemo(nums, iter);
  print(totalLength);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  part2(lines, 25);
  part2(lines, 75);
}
