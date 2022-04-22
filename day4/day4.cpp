#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

std::vector<std::string> readInputs(const std::string& fileName) {
    std::fstream inputs(fileName);
    std::vector<std::string> data;

    std::string line;
    while(!inputs.eof()) {
        inputs >> line;
        data.push_back(line);
    }
    inputs.close();
    return data;
}

void printBoard(std::vector<std::vector<std::string> >& board ) {
    for(auto row : board) {
        for(auto col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void part1(std::vector<std::string>& data) {
    std::stringstream ss(data[0]);
    std::string temp;
    std::queue<std::string> drawNumbersQueue;
    while (getline(ss, temp, ',')) {
        drawNumbersQueue.push(temp);
    }

    std::vector<std::vector<std::vector<std::string> > > boards;
    for(int i = 1; i < data.size(); i += 25) {
        std::vector<std::vector<std::string> > board = 
        {
            { data[i     ], data[i +  1], data[i +  2], data[i +  3], data[i +  4] },
            { data[i +  5], data[i +  6], data[i +  7], data[i +  8], data[i +  9] },
            { data[i + 10], data[i + 11], data[i + 12], data[i + 13], data[i + 14] },
            { data[i + 15], data[i + 16], data[i + 17], data[i + 18], data[i + 19] },
            { data[i + 20], data[i + 21], data[i + 22], data[i + 23], data[i + 24] }
        };
        boards.push_back(board);
    }

    // TODO

}

int main(int argc, char** argv) {
    std::vector<std::string> data = readInputs("day4_test.txt");
    // std::vector<std::string> data = readInputs("day4_input.txt");
    part1(data);
    // part2(data);
    return 0;
}