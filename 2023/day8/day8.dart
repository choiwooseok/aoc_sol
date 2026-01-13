import 'dart:io';

class Node {
  String name = '';
  String left = '';
  String right = '';
}

int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int lcm(int a, int b) => (a ~/ gcd(a, b)) * b;

void part1(String instruction, List<Node> nodes) {
  int ret = 0;
  Node curr = nodes.singleWhere((e) => e.name == 'AAA');
  String inst = instruction;

  while (curr.name != 'ZZZ') {
    for (var dir in inst.split('')) {
      curr = nodes.singleWhere(
        (e) => e.name == (dir == 'L' ? curr.left : curr.right),
      );
      ret++;

      if (curr.name == 'ZZZ') {
        print(ret);
        break;
      }
    }
    inst += instruction;
  }
}

void part2(String instruction, List<Node> nodes) {
  List<int> cycles = [];
  for (var start in nodes.where((e) => e.name.endsWith('A'))) {
    int steps = 0;
    Node curr = start;
    String inst = instruction;
    while (!curr.name.endsWith('Z')) {
      for (var dir in inst.split('')) {
        curr = nodes.singleWhere(
          (e) => e.name == (dir == 'L' ? curr.left : curr.right),
        );
        steps++;
        if (curr.name.endsWith('Z')) break;
      }
      if (curr.name.endsWith('Z')) break;
      inst += instruction;
    }
    cycles.add(steps);
  }

  int result = cycles.reduce((a, b) => lcm(a, b));
  print(result);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n');
  String instruction = lines[0];
  lines.removeAt(0);
  lines.removeAt(0);

  List<Node> nodes = [];
  for (var line in lines) {
    var node = Node();
    node.name = line.split('=')[0].trim();
    node.left = line.split('=')[1].split(',')[0].replaceAll('(', '').trim();
    node.right = line.split('=')[1].split(',')[1].replaceAll(')', '').trim();
    nodes.add(node);
  }

  part1(instruction, nodes);
  part2(instruction, nodes);
}
