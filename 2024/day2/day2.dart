import 'dart:io';
import 'dart:math';

class CubeSet {
  int r = 0;
  int g = 0;
  int b = 0;
}

CubeSet parseCube(String cubeStr) {
  List<String> parts = cubeStr.trim().split(',');

  CubeSet cubeSet = CubeSet();
  for (var part in parts) {
    if (part.contains('green')) {
      cubeSet.g = int.parse(part.replaceAll('green', ''));
    } else if (part.contains('red')) {
      cubeSet.r = int.parse(part.replaceAll('red', ''));
    } else if (part.contains('blue')) {
      cubeSet.b = int.parse(part.replaceAll('blue', ''));
    }
  }
  return cubeSet;
}

bool isPossible(int r, int g, int b, CubeSet cube) {
  return r >= cube.r && g >= cube.g && b >= cube.b;
}

bool areAllCubesPossible(List<CubeSet> cubes) {
  for (var cube in cubes) {
    if (!isPossible(12, 13, 14, cube)) {
      return false;
    }
  }
  return true;
}

int part1(List<String> games) {
  int ret = 0;
  for (int i = 0; i < games.length; i++) {
    List<CubeSet> cubes = games[i]
        .replaceAll('Game ${i + 1}:', '')
        .split(';')
        .map((e) => parseCube(e))
        .toList();

    if (areAllCubesPossible(cubes)) {
      ret += i + 1;
    }
  }

  return ret;
}

int part2(List<String> games) {
  int ret = 0;
  for (int i = 0; i < games.length; i++) {
    List<CubeSet> cubes = games[i]
        .replaceAll('Game ${i + 1}:', '')
        .split(';')
        .map((e) => parseCube(e))
        .toList();

    CubeSet minimum = CubeSet();
    for (var cube in cubes) {
      minimum.r = max(minimum.r, cube.r);
      minimum.g = max(minimum.g, cube.g);
      minimum.b = max(minimum.b, cube.b);
    }

    ret += minimum.r * minimum.g * minimum.b;
  }

  return ret;
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> games = input.split('\n');

  print(part1(games));
  print(part2(games));
}
