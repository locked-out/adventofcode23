#include <cctype>
#include <iostream>
#include <string>
#define N 140

// rectangle with with corners (x0, y0) and [x1, y1]
inline int nSymbolsInRectangle(int nSymbols[N+1][N+1], int x0, int y0, int x1, int y1) {
  int outer = nSymbols[x1][y1];
  int inner = nSymbols[x0][y0];
  return outer - nSymbols[x0][y1] - nSymbols[x1][y0] + inner;
}

int main (int argc, char *argv[]) {


  // nSymbols[i][j] = Number of symbols contained in a rectangle with corners (0,0) and (i,j)
  int nSymbols[N+1][N+1] = {};

  int numbers[N][N]; // the number ending at (i, j)
  int numberLengths[N][N] = {};// the length of the number ending at (i, j), 0 if none

  for (int row = 0; row < N; row++) {
    int symbolsInRow = 0;

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

        symbolsInRow += (c != '.');
      }
      nSymbols[row+1][col+1] = symbolsInRow + nSymbols[row][col+1];
    }

    numberLengths[row][N-1] = numberLength;
    numbers[row][N-1] = number;

  }

  int sumParts = 0;

  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      if (numberLengths[row][col] > 0) {
        int start = col - numberLengths[row][col] + 1;

        int lowerRow = std::max(0, row-1);
        int lowerCol = std::max(0, start-1);

        int upperRow = std::min(N, row+2);
        int upperCol = std::min(N, col+2);

        int surroundingSymbols = nSymbolsInRectangle(nSymbols, 
            lowerRow, lowerCol, upperRow, upperCol);
        
        if (surroundingSymbols > 0)
          sumParts += numbers[row][col];
      }
    }
  }

  std::cout << sumParts << '\n';

  return 0;
}
