import 'dart:io';

class Node {
  String name = '';
  String left = '';
  String right = '';
}

void part1(String instruction, List<Node> nodes) {
  int ret = 0;
  Node curr = nodes.singleWhere((e) => e.name == 'AAA');
  String inst = instruction;

  while (curr.name != 'ZZZ') {
    for (var dir in inst.split('')) {
      curr = nodes
          .singleWhere((e) => e.name == (dir == 'L' ? curr.left : curr.right));
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
  int ret = 0;
  List<Node> currs = nodes.where((e) => e.name.endsWith('A')).toList();
  String inst = instruction;

  while (currs.any((e) => !e.name.endsWith('Z'))) {
    for (var dir in inst.split('')) {
      currs = currs
          .map((curr) => nodes.singleWhere(
              (e) => e.name == (dir == 'L' ? curr.left : curr.right)))
          .toList();
      ret++;

      if (currs.every((e) => e.name.endsWith('Z'))) {
        print(ret);
        break;
      }
    }
    inst += instruction;
  }
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
