import 'dart:io';

class Point {
  int x = 0;
  int y = 0;

  Point(int x, int y) {
    this.x = x;
    this.y = y;
  }

  @override
  bool operator ==(Object other) =>
      other is Point &&
      other.runtimeType == runtimeType &&
      other.x == x &&
      other.y == y;

  @override
  int get hashCode => x.hashCode ^ y.hashCode;
}

void part1(String line) {
  List<Point> points = [];
  points.add(Point(0, 0));

  Point curr = Point(0, 0);
  for (var ch in line.split('')) {
    if (ch == '^') curr.y += 1;
    if (ch == 'v') curr.y -= 1;
    if (ch == '>') curr.x += 1;
    if (ch == '<') curr.x -= 1;

    points.add(Point(curr.x, curr.y));
  }

  print(points.toSet().length);
}

void part2(String line) {
  List<Point> points = [];
  points.add(Point(0, 0));

  Point santa = Point(0, 0);
  Point robot = Point(0, 0);

  for (int i = 0; i < line.length; i++) {
    if (line[i] == '^') (i % 2 == 0) ? santa.y += 1 : robot.y += 1;
    if (line[i] == 'v') (i % 2 == 0) ? santa.y -= 1 : robot.y -= 1;
    if (line[i] == '>') (i % 2 == 0) ? santa.x += 1 : robot.x += 1;
    if (line[i] == '<') (i % 2 == 0) ? santa.x -= 1 : robot.x -= 1;

    points.add(Point(santa.x, santa.y));
    points.add(Point(robot.x, robot.y));
  }

  print(points.toSet().length);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  part1(input);
  part2(input);
}
