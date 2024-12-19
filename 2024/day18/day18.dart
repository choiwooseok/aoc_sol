import 'dart:io';
import 'dart:collection';

class Position {
  final int x;
  final int y;

  Position(this.x, this.y);

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      other is Position &&
          runtimeType == other.runtimeType &&
          x == other.x &&
          y == other.y;

  @override
  int get hashCode => x.hashCode ^ y.hashCode;
}

int findShortestPath(
    Set<Position> corruptedPositions, int targetX, int targetY) {
  Queue<Position> queue = Queue();
  Set<Position> visited = {};
  queue.add(Position(0, 0));
  visited.add(Position(0, 0));

  int steps = 0;
  List<Position> directions = [
    Position(1, 0),
    Position(-1, 0),
    Position(0, 1),
    Position(0, -1)
  ];

  while (queue.isNotEmpty) {
    int size = queue.length;
    for (int i = 0; i < size; i++) {
      Position current = queue.removeFirst();
      if (current.x == targetX && current.y == targetY) {
        return steps;
      }

      for (var direction in directions) {
        int newX = current.x + direction.x;
        int newY = current.y + direction.y;
        Position newPosition = Position(newX, newY);

        if (newX >= 0 &&
            newX <= targetX &&
            newY >= 0 &&
            newY <= targetY &&
            !corruptedPositions.contains(newPosition) &&
            !visited.contains(newPosition)) {
          queue.add(newPosition);
          visited.add(newPosition);
        }
      }
    }
    steps++;
  }

  return -1; // No path found
}

void part1(List<String> lines) {
  Set<Position> corruptedPositions = {};
  for (var line in lines.take(1024)) {
    var parts = line.split(',');
    int x = int.parse(parts[0]);
    int y = int.parse(parts[1]);
    corruptedPositions.add(Position(x, y));
  }

  int minSteps = findShortestPath(corruptedPositions, 70, 70);
  print(minSteps);
}

void part2(List<String> lines) {
  Set<Position> corruptedPositions = {};
  for (int i = 0; i < lines.length; i++) {
    var parts = lines[i].split(',');
    int x = int.parse(parts[0]);
    int y = int.parse(parts[1]);
    corruptedPositions.add(Position(x, y));

    if (findShortestPath(corruptedPositions, 70, 70) == -1) {
      print('$x,$y');
      break;
    }
  }
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n')..removeWhere((e) => e.isEmpty);
  part1(lines);
  part2(lines);
}
