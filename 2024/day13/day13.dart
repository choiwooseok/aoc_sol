import 'dart:io';

bool isInteger(num value) => (value % 1) == 0;

class Equation {
  final int aX;
  final int aY;
  final int bX;
  final int bY;
  final int prizeX;
  final int prizeY;

  Equation(this.aX, this.aY, this.bX, this.bY, this.prizeX, this.prizeY);
}

int solveEquations(int aX, int aY, int bX, int bY, int prizeX, int prizeY) {
  // Using Cramer's rule to solve the system of linear equations
  int determinant = aX * bY - aY * bX;
  if (determinant == 0) {
    print('No unique solution exists.');
    return 0;
  }

  int determinantA = prizeX * bY - prizeY * bX;
  int determinantB = aX * prizeY - aY * prizeX;

  double a = determinantA / determinant.toDouble();
  double b = determinantB / determinant.toDouble();

  if (a >= 0 && b >= 0 && isInteger(a) && isInteger(b)) {
    return 3 * a.toInt() + b.toInt();
  }

  return 0;
}

List<Equation> parseLines(List<String> lines) {
  List<Equation> equations = [];
  for (int i = 0; i < lines.length; i += 3) {
    var aParts = lines[i].split(', ');
    var bParts = lines[i + 1].split(', ');
    var prizeParts = lines[i + 2].split(', ');

    int aX = int.parse(aParts[0].split('+')[1]);
    int aY = int.parse(aParts[1].split('+')[1]);
    int bX = int.parse(bParts[0].split('+')[1]);
    int bY = int.parse(bParts[1].split('+')[1]);
    int prizeX = int.parse(prizeParts[0].split('=')[1]);
    int prizeY = int.parse(prizeParts[1].split('=')[1]);

    equations.add(Equation(aX, aY, bX, bY, prizeX, prizeY));
  }
  return equations;
}

void part1(List<String> lines) {
  List<Equation> equations = parseLines(lines);
  int ret = 0;
  for (var eq in equations) {
    ret += solveEquations(eq.aX, eq.aY, eq.bX, eq.bY, eq.prizeX, eq.prizeY);
  }
  print(ret);
}

void part2(List<String> lines) {
  List<Equation> equations = parseLines(lines);
  int ret = 0;
  for (var eq in equations) {
    ret += solveEquations(eq.aX, eq.aY, eq.bX, eq.bY,
        eq.prizeX + 10000000000000, eq.prizeY + 10000000000000);
  }
  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n')..removeWhere((e) => e.isEmpty);
  part1(lines);
  part2(lines);
}
