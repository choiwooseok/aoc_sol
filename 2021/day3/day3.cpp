#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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

int binaryToDecimal(const std::string& n) {
    std::string num = n;
    int dec_value = 0;
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

// key -> index
// value {0 cnt, 1 cnt}
std::map<int, std::pair<int, int> > countHelper(const std::vector<std::string>& data) {
    std::map<int, std::pair<int, int> > counts;
    for(auto& elem : data) {
        for(int i = 0; i < elem.size(); i++) {
            if(elem[i] == '0') {
                counts[i].first++;
            } else {
                counts[i].second++;
            }
        }
    }
    return counts;
}

std::pair<std::string, std::string> getGammaNEpsilon(std::map<int, std::pair<int, int> >& counts) {
    std::string gamma = "";
    std::string epsilon = "";
    for(auto& count : counts) {
        int zeros = count.second.first;
        int ones = count.second.second;

        gamma.append(std::to_string(zeros > ones ? 0 : 1)); 
        epsilon.append(std::to_string(zeros > ones ? 1 : 0)); 
    }
    return {gamma, epsilon};
}

void part1(std::vector<std::string>& data) {
    std::map<int, std::pair<int, int> > counts = countHelper(data);
    std::pair<std::string, std::string> ge = getGammaNEpsilon(counts);
    std::cout << binaryToDecimal(ge.first) * binaryToDecimal(ge.second) << std::endl;
}

std::vector<std::string> filter(std::vector<std::string>& data, int idx, bool most) {
    std::map<int, std::pair<int, int> > counts = countHelper(data);

    int zeros = counts[idx].first;
    int ones = counts[idx].second;

    char target;
    if(most) {
        target = zeros > ones ? '0' : '1';
    } else {
        target = zeros > ones ? '1' : '0';
    }

    std::vector<std::string> filtered;

    for(auto& elem : data) {
        if(elem[idx] == target) {
            filtered.push_back(elem);
        }
    }

    // for(auto& elem : filtered) {
    //     std::cout << elem << " ";
    // }
    // std::cout << std::endl;

    return filtered;
}

void part2(std::vector<std::string>& data) {
    int idx = 0;
    std::vector<std::string> oxy = filter(data, idx, true);
    idx++;
    while(oxy.size() > 1) {
        oxy = filter(oxy, idx, true);
        idx++;
    }

    idx = 0;
    std::vector<std::string> co2 = filter(data, idx, false);
    idx++;
    while(co2.size() > 1) {
        co2 = filter(co2, idx, false);
        idx++;
    }

    std::cout << binaryToDecimal(oxy[0]) * binaryToDecimal(co2[0]) << std::endl;
}

int main(int argc, char** argv) {
    // std::vector<std::string> data = readInputs("day3_test.txt");
    std::vector<std::string> data = readInputs("day3_input.txt");
    part1(data);
    part2(data);
    return 0;
}