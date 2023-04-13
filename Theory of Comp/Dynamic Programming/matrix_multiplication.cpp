#include <iostream>
#include <stack>



#define MAXSIZE 11	
#define MATRIXSIZE 8		


//I did use an online source for this, struggled quite a bit with the printing of the order
void find_mult_ord(int i, int j, int n, int* bracket, char& name) {
    if (i == j) {

        std::cout << name++;

        return;
    }

    std::cout << "(";
    find_mult_ord(i, *((bracket + i * n) + j), n, bracket, name);
    find_mult_ord(*((bracket + i * n) + j) + 1, j, n, bracket, name);
    std::cout << ")";
}


//did not like working with vectors of vectors, opted for standard double int arrays
int find_min(int M[MATRIXSIZE][MATRIXSIZE], int K[MATRIXSIZE][MATRIXSIZE], int A[MAXSIZE], int i, int j) {
    int k = i;
    std::stack < int > min_stack;


    min_stack.push(M[i][j]);

    for (k; k < j; k++) {

        M[i][j] = M[i][k] + M[k + 1][j] + A[i - 1] * A[k] * A[j];

        if (min_stack.top() > M[i][j] || min_stack.top() == -1) {
            K[i][j] = k;
            min_stack.pop();
            min_stack.push(M[i][j]);
        }
    }

    return min_stack.top();
}

int K[MATRIXSIZE][MATRIXSIZE];

int main() {

    //matrixs in the handout
    int A[MAXSIZE] = {
      10,
      17,
      12,
      25,
      14,
      30,
      15,
      9
    };
    int M[MATRIXSIZE][MATRIXSIZE];

    //use -1 flag for non diagonals
    for (int i = 1; i < MATRIXSIZE; i++) {
        for (int j = 1; j < MATRIXSIZE; j++) {
            M[i][j] = -1;
            K[i][j] = -1;
        }
    }

    //set diagonals to 0
    for (int i = 1; i < MATRIXSIZE; i++) {
        M[i][i] = 0;
        K[i][i] = 0;
    }


    int j = 0;
    for (int l = 1; l < MATRIXSIZE - 1; l++) {
        for (int i = 1; i < MATRIXSIZE - l; i++) {
            j = i + l;
            M[i][j] = find_min(M, K, A, i, j);
        }
    }
    std::cout << "\n";

   
    for (int i = 1; i < MATRIXSIZE; i++) {
        for (int j = 1; j < MATRIXSIZE; j++) {
            //set -1 to X to mimic table
            if (M[i][j] == -1) {
                std::cout << "X " << " ";
            }
            else {
                std::cout << M[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "min work: " << M[1][MATRIXSIZE - 1] << "\n";

    
    char name = 'A';
    find_mult_ord(1, MATRIXSIZE - 1, MATRIXSIZE, (int*)K, name);
    std::cout << "\n";
    return 0;
}