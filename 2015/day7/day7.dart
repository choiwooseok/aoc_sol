import 'dart:io';

class Node {
  String name = '';
  String val = '';
}

bool isEvaluated(List<Node> nodes, String name) {
  return nodes.where((element) => element.name == name).isNotEmpty &&
      nodes.firstWhere((element) => element.name == name).val.isNotEmpty;
}

bool isInt(String s) {
  return int.tryParse(s) != null;
}

void processLines(List<String> lines, {bool isPart2 = false}) {
  List<Node> nodes = [];

  while (nodes.length != lines.length) {
    for (var line in lines) {
      List<String> parts = line.split(' -> ');
      List<String> lhs = parts[0].split(' ');

      Node node = Node();
      node.name = parts[1];

      if (lhs.length == 1) {
        node.val = (isPart2 && node.name == 'b') ? '46065' : lhs[0];
      } else if (lhs.length == 2) {
        if (isInt(lhs[1])) {
          node.val = lhs[1];
        } else if (isEvaluated(nodes, lhs[1])) {
          node.val = (~int.parse(nodes
                      .firstWhere((element) => element.name == lhs[1])
                      .val) &
                  0xFFFF)
              .toString();
        } else {
          continue;
        }
      } else {
        bool l_isEvaluated = isEvaluated(nodes, lhs[0]);
        bool r_isEvaluated = isEvaluated(nodes, lhs[2]);
        bool l_isInt = isInt(lhs[0]);
        bool r_isInt = isInt(lhs[2]);

        if (!(l_isEvaluated || l_isInt) || !(r_isEvaluated || r_isInt))
          continue;

        int l_val = l_isInt
            ? int.parse(lhs[0])
            : int.parse(
                nodes.firstWhere((element) => element.name == lhs[0]).val);
        int r_val = r_isInt
            ? int.parse(lhs[2])
            : int.parse(
                nodes.firstWhere((element) => element.name == lhs[2]).val);

        switch (lhs[1]) {
          case 'AND':
            node.val = (l_val & r_val & 0xFFFF).toString();
            break;
          case 'OR':
            node.val = (l_val | r_val & 0xFFFF).toString();
            break;
          case 'LSHIFT':
            node.val = (l_val << r_val & 0xFFFF).toString();
            break;
          case 'RSHIFT':
            node.val = (l_val >> r_val & 0xFFFF).toString();
            break;
          default:
            continue;
        }
      }

      nodes.where((element) => element.name == parts[1]).isEmpty
          ? nodes.add(node)
          : nodes.firstWhere((element) => element.name == parts[1]).val =
              node.val;
    }
  }

  print(nodes.firstWhere((element) => element.name == 'a').val);
  print(nodes.firstWhere((element) => element.name == 'lx').val);
}

void main() {
  List<String> input = File('input.txt').readAsStringSync().split('\n');

  processLines(input);
  processLines(input, isPart2: true);
}
