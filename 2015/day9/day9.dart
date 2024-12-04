import 'dart:io';

class Path {
  String from = '';
  String to = '';
  int distance = 0;

  String toString() {
    return '$from -> $to: $distance';
  }
}

List<String> getPermutation(List<String> source) {
  List allPermutations = [];

  void permutate(List list, int cursor) {
    if (cursor == list.length) {
      allPermutations.add(list);
      return;
    }

    for (int i = cursor; i < list.length; i++) {
      List permutation = new List.from(list);
      permutation[cursor] = list[i];
      permutation[i] = list[cursor];
      permutate(permutation, cursor + 1);
    }
  }

  permutate(source, 0);

  List<String> strPermutations = [];
  for (List permutation in allPermutations) {
    strPermutations.add(permutation.join('->'));
  }

  return strPermutations;
}

void part1(List<String> lines) {
  List<Path> paths = [];
  for (var line in lines) {
    List<String> part = line.split(' = ');
    List<String> cities = part[0].split(' to ');
    paths.add(Path()
      ..from = cities[0]
      ..to = cities[1]
      ..distance = int.parse(part[1]));
  }

  Set<String> cities =
      (paths.map((e) => e.from).toList() + paths.map((e) => e.to).toList())
          .toSet();

  List<String> permutations = getPermutation(cities.toList());

  int minDistance = 1000000;
  for (var permutation in permutations) {
    List<String> cities = permutation.split('->');
    int distance = 0;
    for (int i = 0; i < cities.length - 1; i++) {
      Path path = paths.firstWhere((element) =>
          (element.from == cities[i] && element.to == cities[i + 1]) ||
          (element.to == cities[i] && element.from == cities[i + 1]));
      distance += path.distance;
    }
    if (distance < minDistance) {
      minDistance = distance;
    }
  }

  print(minDistance);
}

void part2(List<String> lines) {
  List<Path> paths = [];
  for (var line in lines) {
    List<String> part = line.split(' = ');
    List<String> cities = part[0].split(' to ');
    paths.add(Path()
      ..from = cities[0]
      ..to = cities[1]
      ..distance = int.parse(part[1]));
  }

  Set<String> cities =
      (paths.map((e) => e.from).toList() + paths.map((e) => e.to).toList())
          .toSet();

  List<String> permutations = getPermutation(cities.toList());

  int maxDistance = -1;
  for (var permutation in permutations) {
    List<String> cities = permutation.split('->');
    int distance = 0;
    for (int i = 0; i < cities.length - 1; i++) {
      Path path = paths.firstWhere((element) =>
          (element.from == cities[i] && element.to == cities[i + 1]) ||
          (element.to == cities[i] && element.from == cities[i + 1]));
      distance += path.distance;
    }
    if (distance > maxDistance) {
      maxDistance = distance;
    }
  }

  print(maxDistance);
}

void main() {
  List<String> input = File('input.txt').readAsStringSync().split('\n');
  part1(input);
  part2(input);
}
