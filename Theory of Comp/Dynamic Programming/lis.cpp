#include <iostream>

#include <fstream>

#include <stdlib.h>

#include <stack>

#include <string>
#include <vector>


#define MAXSIZE 16 

void printArray(std::vector<int> & Array, int size) {
    for (int i = 1; i < size + 1; i++) {
        std::cout << Array[i] << " ";
    }
    std::cout << "\n";
}

//find LIS algo
void findLIS(std::vector<int> & input, std::vector<int> & DP, int size, int max) {
    std::stack <int> temp_stack;
    temp_stack.push(DP[1]);

    int i = 1;
    std::cout << input[i] << " ";
    while (temp_stack.top() != max) {

        //checks for change in DP
        if (DP[i] > temp_stack.top()) {

            temp_stack.pop();
            temp_stack.push(DP[i]);
            std::cout << input[i] << " ";
        }
        i++;
    }
    std::cout << "\n";
}
//traverses the array of values and stores their possible string lengths
//in DP for each index
//use stack for max length, new longer takes top
int max_length(std::vector<int>& input, std::vector<int>& DP, int size) {
    std::stack < int > max_stack;

    //needs 2 loops, 1 for traversing left to right
    //and the other for checking values from left-right behind the index
    for (int i = 2; i < size + 1; i++) {

        int max = 0;

        for (int j = 1; j < i; j++) {

            if (input[i] > input[j]) {

                if (DP[j] > max) {
                    max = DP[j];
                }
            }
        }
        DP[i] = max + 1;
    }

    //stack to check the highest value and loop through to find it
    max_stack.push(DP[1]);
    for (int i = 2; i < size + 1; i++) {

        if (max_stack.top() < DP[i]) {
            max_stack.pop();
            max_stack.push(DP[i]);
        }
    }
    return max_stack.top();
}

int main() {

    std::vector<int> input(MAXSIZE);
    int i = 0;
    std::ifstream file_name("incseq.txt");
    std::string line;
    
    while (std::getline(file_name, line)) {
        int temp = std::stoi(line);
        input[i] = temp;
        i++;
    }
    
    file_name.close();
    std::vector<int> DP(i + 1);
    DP[1] = 1;

    int max_LIS = max_length(input, DP, i);

    printArray(input, i);
    std::cout << "Max length is: " << max_LIS << "\n";
    findLIS(input, DP, i, max_LIS);
    return 0;
    }

  