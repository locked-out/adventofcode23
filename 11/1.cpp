#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> expand_space(std::vector<int> &gs) {
  std::vector<int> expanded(gs.size());
  expanded[0] = gs[0];

  int expansion = 0;
  for (int i = 1; i < gs.size(); i++) {
    int empty_space = gs[i] - gs[i-1] -1;
    if (empty_space > 0) {
      expansion += empty_space;
    }
    expanded[i] = gs[i] + expansion;
  }
  
  return expanded;
}

int sum_pairs_difs(std::vector<int> &gs) {
  // sum of all distances
  // for each point i in increasing position:
  //  point i will be subtracted n-i-1 times
  //  point i will be added i times
  //  sum += i * v[i] - (n-i-1) * v[i]
  //  sum += v[i] * (2*i - n + 1)
  
  int sum = 0;
  for (int i = 0; i < gs.size(); i++) {
    sum += gs[i] * (2*i - gs.size() + 1);
  }

  return sum;
}

int main (int argc, char *argv[]) {
  std::vector<int> galaxiesX;
  std::vector<int> galaxiesY;

  int row = 0;
  for (std::string line; std::getline(std::cin, line); row++) {
    std::stringstream line_stream(line);
    int col = 0;
    
    for (char c; line_stream >> c; col++) {
      if (c == '#') {
        galaxiesX.push_back(col);
        galaxiesY.push_back(row);
      }
    } 
  }

  std::sort(galaxiesX.begin(), galaxiesX.end());

  galaxiesX = expand_space(galaxiesX);
  galaxiesY = expand_space(galaxiesY);

  int xDifs = sum_pairs_difs(galaxiesX);
  int yDifs = sum_pairs_difs(galaxiesY);
  printf("%d + %d = %d\n", xDifs, yDifs, xDifs+yDifs);

  return 0;
}
