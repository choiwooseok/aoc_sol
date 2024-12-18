import 'dart:io';

enum OpCode { adv, bxl, bst, jnz, bxc, out, bdv, cdv }

int combo(int operand, int a, int b, int c) {
  switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
      return operand;
    case 4:
      return a;
    case 5:
      return b;
    case 6:
      return c;
    default:
      throw Exception('Invalid combo operand');
  }
}

List<int> run(int a, int b, int c, List<int> program) {
  int ptr = 0;
  List<int> output = [];

  while (ptr < program.length) {
    int opcode = program[ptr];
    int operand = program[ptr + 1];

    switch (OpCode.values[opcode]) {
      case OpCode.adv:
        a ~/= (1 << combo(operand, a, b, c));
        ptr += 2;
        break;
      case OpCode.bxl:
        b ^= operand;
        ptr += 2;
        break;
      case OpCode.bst:
        b = combo(operand, a, b, c) % 8;
        ptr += 2;
        break;
      case OpCode.jnz:
        if (a != 0) {
          ptr = operand;
        } else {
          ptr += 2;
        }
        break;
      case OpCode.bxc:
        b ^= c;
        ptr += 2;
        break;
      case OpCode.out:
        int value = combo(operand, a, b, c);
        output.add(value % 8);
        ptr += 2;
        break;
      case OpCode.bdv:
        b = a ~/ (1 << combo(operand, a, b, c));
        ptr += 2;
        break;
      case OpCode.cdv:
        c = a ~/ (1 << combo(operand, a, b, c));
        ptr += 2;
        break;
    }
  }
  return output;
}

void part1(List<String> lines) {
  int a = int.parse(lines[0].split(': ')[1]);
  int b = 0;
  int c = 0;
  List<int> program =
      lines[3].split(': ')[1].split(',').map(int.parse).toList();
  List<int> output = run(a, b, c, program);
  print(output.join(','));
}

void part2(List<String> lines) {
  // TODO

//   int a = int.parse(lines[0].split(': ')[1]) * 854000;
//   int b = 0;
//   int c = 0;
//   List<int> program =
//       lines[3].split(': ')[1].split(',').map(int.parse).toList();
//   List<int> output = run(a, b, c, program);
//   print(output.join(','));
//   print('2,4,1,2,7,5,1,7,4,4,0,3,5,5,3,0');
}

void main() {
  String input = File('input.txt').readAsStringSync();
  List<String> lines = input.split('\n')..removeWhere((e) => e.isEmpty);
  part1(lines);
  part2(lines);
}
