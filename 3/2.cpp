#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#define N 140

struct gear {
  int adjacencies;
  int product;
};

int main (int argc, char *argv[]) {

  
  int gears[N][N] = {};

  int ngears = 0;
  std::vector<struct gear> gearList;

  int numbers[N][N]; // the number ending at (i, j)
  int numberLengths[N][N] = {};// the length of the number ending at (i, j), 0 if none

  for (int row = 0; row < N; row++) {
    int numberLength = 0;
    int number = 0;  
    for (int col = 0; col < N; col++) {
      char c;
      std::cin >> c;
  
      if (isdigit(c)) {
        c -= '0';
        numberLength++;
        number = (number * 10) + c;
      } else {
        if (col > 0) {
          numberLengths[row][col-1] = numberLength;
          numbers[row][col-1] = number;
          numberLength = 0;
          number = 0;
        }

        if (c == '*') {
          gears[row][col] = ++ngears;
          struct gear g = {};
          g.product = 1;
          gearList.push_back(g);
        }
      }
    }

    numberLengths[row][N-1] = numberLength;
    numbers[row][N-1] = number;

  }

  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      if (numberLengths[row][col] > 0) {
        int start = col - numberLengths[row][col] + 1;

        int lowerRow = std::max(0, row-1);
        int lowerCol = std::max(0, start-1);

        int upperRow = std::min(N-1, row+1);
        int upperCol = std::min(N-1, col+1);

        for (int r = lowerRow; r <= upperRow; r++) {
          for (int c = lowerCol; c <= upperCol; c++) {
            if (gears[r][c]) {
              struct gear *g = &gearList[gears[r][c] - 1];
              g->adjacencies++;
              g->product *= numbers[row][col];
            }
          }
        }  
      }
    }
  }

  int sumGears = 0;

  for (struct gear g : gearList) {
    if (g.adjacencies == 2) sumGears += g.product;
  }

  std::cout << sumGears << '\n';

  return 0;
}
