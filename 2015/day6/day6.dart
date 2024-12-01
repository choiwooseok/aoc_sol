import 'dart:io';

void part1(List<String> lines) {
  List<List<bool>> grid =
      List.generate(1000, (_) => List.generate(1000, (_) => false));
  List<String> cmd = ['turn on', 'turn off', 'toggle'];

  for (var line in lines) {
    for (int k = 0; k < cmd.length; k++) {
      if (line.contains(cmd[k])) {
        line = line.substring(cmd[k].length).trim();
        List<String> part = line.split(' through ');
        List<int> from = part[0].split(',').map(int.parse).toList();
        List<int> to = part[1].split(',').map(int.parse).toList();

        for (int i = from[0]; i <= to[0]; i++) {
          for (int j = from[1]; j <= to[1]; j++) {
            if (k == 0) grid[i][j] = true;
            if (k == 1) grid[i][j] = false;
            if (k == 2) grid[i][j] = !grid[i][j];
          }
        }
        break;
      }
    }
  }

  int ret = grid.fold(0, (sum, row) => sum + row.where((cell) => cell).length);
  print(ret);
}

void part2(List<String> lines) {
  List<List<int>> grid =
      List.generate(1000, (_) => List.generate(1000, (_) => 0));
  List<String> cmd = ['turn on', 'turn off', 'toggle'];

  for (var line in lines) {
    for (int k = 0; k < cmd.length; k++) {
      if (line.contains(cmd[k])) {
        line = line.substring(cmd[k].length).trim();
        List<String> part = line.split(' through ');
        List<int> from = part[0].split(',').map(int.parse).toList();
        List<int> to = part[1].split(',').map(int.parse).toList();

        for (int i = from[0]; i <= to[0]; i++) {
          for (int j = from[1]; j <= to[1]; j++) {
            if (k == 0) grid[i][j] += 1;
            if (k == 1) grid[i][j] = (grid[i][j] > 0) ? grid[i][j] - 1 : 0;
            if (k == 2) grid[i][j] += 2;
          }
        }
        break;
      }
    }
  }

  int ret = grid.fold(0, (sum, row) => sum + row.reduce((a, b) => a + b));
  print(ret);
}

void main() {
  String input = File('input.txt').readAsStringSync();
  part1(input.split('\n'));
  part2(input.split('\n'));
}
