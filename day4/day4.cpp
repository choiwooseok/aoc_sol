#include <iostream>
#include <iomanip> 
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

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

void dataManipulate(std::vector<std::string>& data, std::queue<std::string>& drawNumbersQueue, std::vector<std::vector<std::vector<std::pair<std::string, bool> > > >& boards) {
    std::stringstream ss(data[0]);
    std::string temp;

    while (getline(ss, temp, ',')) {
        drawNumbersQueue.push(temp);
    }

    for(int i = 1; i < data.size(); i += 25) {
        std::vector<std::vector<std::pair<std::string, bool> > > board = 
        {
            { { data[i     ], false }, { data[i +  1], false }, { data[i +  2], false }, { data[i +  3], false }, { data[i +  4], false } },
            { { data[i +  5], false }, { data[i +  6], false }, { data[i +  7], false }, { data[i +  8], false }, { data[i +  9], false } },
            { { data[i + 10], false }, { data[i + 11], false }, { data[i + 12], false }, { data[i + 13], false }, { data[i + 14], false } },
            { { data[i + 15], false }, { data[i + 16], false }, { data[i + 17], false }, { data[i + 18], false }, { data[i + 19], false } },
            { { data[i + 20], false }, { data[i + 21], false }, { data[i + 22], false }, { data[i + 23], false }, { data[i + 24], false } }
        };
        boards.push_back(board);
    }
}

void printBoard(std::vector<std::vector<std::pair<std::string, bool> > >& board ) {
    for(auto row : board) {
        for(auto col : row) {
            std::cout << std::setw(10) << col.first << " " << std::setw(10) << std::boolalpha << col.second << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int getUnmarkedSum(const std::vector<std::vector<std::pair<std::string, bool> > >& winningBoard) {
    int unmarkedSum = 0;
    for(auto& row : winningBoard) {
        for(auto& col : row) {
            if(col.second == false) {
                unmarkedSum += std::stoi(col.first);
            }
        }
    }
    return unmarkedSum;
}

void part1(std::vector<std::string>& data) {
    std::queue<std::string> drawNumbersQueue;
    std::vector<std::vector<std::vector<std::pair<std::string, bool> > > > boards;

    dataManipulate(data, drawNumbersQueue, boards);

    bool hasWinner = false;
    std::vector<std::vector<std::pair<std::string, bool> > > winningBoard;

    std::string drawNumber = drawNumbersQueue.front();
    while(!drawNumbersQueue.empty()) {
        drawNumber = drawNumbersQueue.front();
        for(auto& board : boards) {
            for(auto& row : board) {
                for(auto& col : row) {
                    if(col.first == drawNumber) {
                        col.second = true;
                    }
                }
            }
        }

        int rCnt = 0;
        int cCnt = 0;
        for(auto& board : boards) {
            for(int i = 0; i < 5; i++) {
                rCnt = 0;
                cCnt = 0;
                for(int j = 0; j < 5; j++) {
                    // row checker
                    if(board[i][j].second == true) {
                        rCnt++;
                    }
                    // column checker
                    if(board[j][i].second == true) {
                        cCnt++;
                    }
                    if(rCnt == 5 || cCnt == 5) {
                        hasWinner = true;
                        break;
                    }
                }
            }
            if(hasWinner) {
                winningBoard = board;
                printBoard(winningBoard);
                break;
            }
        }
        drawNumbersQueue.pop();
        if(hasWinner) {
            break;
        }
    }

    int unmarkedSum = getUnmarkedSum(winningBoard);
    std::cout << "unmarkedSum : " << unmarkedSum << " last draw " << drawNumber << " mul : "<< unmarkedSum * std::stoi(drawNumber) << std::endl;
}

void part2(std::vector<std::string>& data) {
    std::queue<std::string> drawNumbersQueue;
    std::vector<std::vector<std::vector<std::pair<std::string, bool> > > > boards;
    dataManipulate(data, drawNumbersQueue, boards);

    bool hasWinner = false;
    bool lastBoardFin = false;
    std::vector<std::vector<std::pair<std::string, bool> > > lastBoard;
    std::vector<int> alreadyWin;

    std::string drawNumber = drawNumbersQueue.front();
    while(!drawNumbersQueue.empty()) {
        drawNumber = drawNumbersQueue.front();
        for(auto& board : boards) {
            for(auto& row : board) {
                for(auto& col : row) {
                    if(col.first == drawNumber) {
                        col.second = true;
                    }
                }
            }
        }

        int rCnt = 0;
        int cCnt = 0;
        for(int k = 0; k < boards.size(); k++) {
            hasWinner = false;

            if(std::find(alreadyWin.begin(), alreadyWin.end(), k) == alreadyWin.end()) {
                for(int i = 0; i < 5; i++) {
                    rCnt = 0;
                    cCnt = 0;
                    for(int j = 0; j < 5; j++) {
                        // row checker
                        if(boards[k][i][j].second == true) {
                            rCnt++;
                        }
                        // column checker
                        if(boards[k][j][i].second == true) {
                            cCnt++;
                        }
                        if(rCnt == 5 || cCnt == 5) {
                            hasWinner = true;
                            break;
                        }
                    }
                }
                if(hasWinner) {
                    alreadyWin.push_back(k);

                    if(alreadyWin.size() == boards.size()) {
                        lastBoard = boards[k];
                        lastBoardFin = true;
                        break;
                    }
                }
            }
        }

        if(lastBoardFin) {
            printBoard(lastBoard);
            break;
        }
        drawNumbersQueue.pop();
    }

    int unmarkedSum = getUnmarkedSum(lastBoard);
    std::cout << "unmarkedSum : " << unmarkedSum << " last draw " << drawNumber << " mul : "<< unmarkedSum * std::stoi(drawNumber) << std::endl;

}

int main(int argc, char** argv) {
    // std::vector<std::string> data = readInputs("day4_test.txt");
    std::vector<std::string> data = readInputs("day4_input.txt");
    part1(data);
    part2(data);
    return 0;
}