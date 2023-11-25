#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::vector<int>> Allocation;
std::vector<std::vector<int>> Max;
std::vector<int> Available;

std::vector<int> split(std::string); 
void input();

int main() {
    input();

    int p = Allocation.size(); // Number of processes
    int r = Available.size(); // Number of resources

    int need[p][r];
    int finish[p];
    int safe[p];
    int safeItr = 0;
    bool done = false;

    for (int i = 0; i < p; i++) {
        finish[i] = 0;
        safe[i] = 0;
    }

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = Max[i][j] - Allocation[i][j];


    while (!done) {
        for (int i = 0; i < p; i++) {
            if (finish[i] != 0) continue;
            int flag = 0;

            for (int j = 0; j < r; j++) {
                if (need[i][j] > Available[j]) {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1) continue;

            safe[safeItr++] = i;
            finish[i] = 1;
            for (int k = 0; k < r; k++)
                Available[k] += Allocation[i][k];
        }

        done = true;

        for (int i = 0; i < p; i++){
            if (finish[i] == 0)
                done = false;
        }
    }

    // Print safe sequence

    std::cout << "The safe sequence is: ";

    for (auto i: safe) {
        std::cout << "P" << i << " ";
    }

    std::cout << std::endl;
}

std::vector<int> split(std::string str) {
    std::stringstream ss(str);
    std::vector<int> ret;

    for (std::string w; ss >> w; )
        ret.push_back(std::stoi(w));

    return ret;
}

void input() {
    std::ifstream file;

    file.open("input.txt");

    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        std::exit(-1);
    }

    char buf[10];

    std::vector<std::string> lines;

    while (file.getline(buf, 10) && !file.eof())
        lines.push_back(buf);

    int i = 0;

    while (lines[i] != "")
        Allocation.push_back(split(lines[i++]));

    i++;

    while (lines[i] != "")
        Max.push_back(split(lines[i++]));

    i++;

    Available = split(lines[i]);
}