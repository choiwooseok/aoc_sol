#include <iostream>
#include <vector>
#include <limits>
#include <random>

void printInputs(const std::vector<int> &inputs) {
  std::cout << "answer : ";
  for (auto &elem : inputs) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void sol(std::vector<int> &inputs) {
  for (int i = 0, n = inputs.size(); i < n; i++) {
    if (i % 4 == 0) {
      int op_code = inputs[i];
      int var1 = n > inputs[i + 1] ? inputs[inputs[i + 1]] : std::numeric_limits<int>::min();
      int var2 = n > inputs[i + 2] ? inputs[inputs[i + 2]] : std::numeric_limits<int>::min();
      int idx = n > inputs[i + 3] ? inputs[i + 3] : std::numeric_limits<int>::min();

      if (idx != std::numeric_limits<int>::min()) {
        switch (op_code) {
          case 1:  // ADD
            inputs[idx] = var1 + var2;
            break;
          case 2:  // MUL
            inputs[idx] = var1 * var2;
            break;
          case 99:  // FIN
          default:
            break;
        }
      }
    }
  }
  printInputs(inputs);
}

int main(int argc, char **argv) {
  std::vector<std::vector<int> > test_cases = {
      {1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50},
      {2, 3, 0, 3, 99},
      {2, 4, 4, 5, 99, 0},
      {1, 1, 1, 4, 99, 5, 6, 0, 99}};

  for (auto &test : test_cases) {
    sol(test);
  }

  {
    // part 1
    std::vector<int> inputs = {1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 1, 10, 19, 2, 6, 19, 23, 1, 23, 5, 27, 1, 27, 13, 31, 2, 6, 31, 35, 1, 5, 35, 39, 1, 39, 10, 43, 2, 6, 43, 47, 1, 47, 5, 51, 1, 51, 9, 55, 2, 55, 6, 59, 1, 59, 10, 63, 2, 63, 9, 67, 1, 67, 5, 71, 1, 71, 5, 75, 2, 75, 6, 79, 1, 5, 79, 83, 1, 10, 83, 87, 2, 13, 87, 91, 1, 10, 91, 95, 2, 13, 95, 99, 1, 99, 9, 103, 1, 5, 103, 107, 1, 107, 10, 111, 1, 111, 5, 115, 1, 115, 6, 119, 1, 119, 10, 123, 1, 123, 10, 127, 2, 127, 13, 131, 1, 13, 131, 135, 1, 135, 10, 139, 2, 139, 6, 143, 1, 143, 9, 147, 2, 147, 6, 151, 1, 5, 151, 155, 1, 9, 155, 159, 2, 159, 6, 163, 1, 163, 2, 167, 1, 10, 167, 0, 99, 2, 14, 0, 0};
    inputs[1] = 12;
    inputs[2] = 2;
    sol(inputs);
  }

  {
    // part 2
    std::vector<int> origin = {1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 1, 10, 19, 2, 6, 19, 23, 1, 23, 5, 27, 1, 27, 13, 31, 2, 6, 31, 35, 1, 5, 35, 39, 1, 39, 10, 43, 2, 6, 43, 47, 1, 47, 5, 51, 1, 51, 9, 55, 2, 55, 6, 59, 1, 59, 10, 63, 2, 63, 9, 67, 1, 67, 5, 71, 1, 71, 5, 75, 2, 75, 6, 79, 1, 5, 79, 83, 1, 10, 83, 87, 2, 13, 87, 91, 1, 10, 91, 95, 2, 13, 95, 99, 1, 99, 9, 103, 1, 5, 103, 107, 1, 107, 10, 111, 1, 111, 5, 115, 1, 115, 6, 119, 1, 119, 10, 123, 1, 123, 10, 127, 2, 127, 13, 131, 1, 13, 131, 135, 1, 135, 10, 139, 2, 139, 6, 143, 1, 143, 9, 147, 2, 147, 6, 151, 1, 5, 151, 155, 1, 9, 155, 159, 2, 159, 6, 163, 1, 163, 2, 167, 1, 10, 167, 0, 99, 2, 14, 0, 0};
    std::vector<int> inputs = origin;

    std::random_device rd;   // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 99);

    while (inputs[0] != 19690720) {
      inputs[1] = distrib(gen);  // noun
      inputs[2] = distrib(gen);  // verb
      sol(inputs);
      if (inputs[0] == 19690720) {
        std::cout << 100 * inputs[1] + inputs[2] << std::endl;
        break;
      }
      inputs = origin;
    }
  }

  return 0;
}