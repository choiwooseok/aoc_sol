#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> readInputs(const std::string& fileName) {
    std::fstream inputs(fileName);
    std::vector<int> data;

    std::string line;
    std::string temp;
    while (getline(inputs, temp, ',')) {
        data.push_back(std::stoi(temp));
    }
    inputs.close();
    return data;
}


void part1(std::vector<int>& data, int& days) {
    int cnt = 0;
    for(auto& elem : data) {
        if(elem == 0) {
            elem = 6;
            cnt++;
        } else {
            elem -= 1;
        }
    }

    for(int i = 0; i < cnt; i++) {
        data.push_back(8);
    }

    if(days > 1) {
        days -= 1;
        part1(data, days);
    } else {
        std::cout << data.size() << std::endl;
    }
}

void part2(std::vector<int>& data, int& days) {
}

int main(int argc, char** argv) {
    std::vector<int> data = readInputs("day6_test.txt");
    // std::vector<int> data = readInputs("day6_input.txt");
    int targetDays = 80;
    part1(data, targetDays);

    // part2(data, targetDays);
    return 0;
}