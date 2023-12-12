#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define PART_1 1
#define PART_2 999999
#define SPACE_MULTIPLIER PART_2

std::vector<long long> expand_space(std::vector<long long> &gs) {
  std::vector<long long> expanded(gs.size());
  expanded[0] = gs[0];

  long long expansion = 0;
  for (std::size_t i = 1; i < gs.size(); i++) {
    int empty_space = gs[i] - gs[i-1] -1;
    if (empty_space > 0) {
      expansion += empty_space * SPACE_MULTIPLIER;
    }
    expanded[i] = gs[i] + expansion;
  }
  
  return expanded;
}

long long sum_pairs_difs(std::vector<long long> &gs) {
  // sum of all distances
  // for each point i in increasing position:
  //  point i will be subtracted n-i-1 times
  //  point i will be added i times
  //  sum += i * v[i] - (n-i-1) * v[i]
  //  sum += v[i] * (2*i - n + 1)
  
  long long sum = 0;
  for (std::size_t i = 0; i < gs.size(); i++) {
    sum += gs[i] * (2*i - gs.size() + 1);
  }

  return sum;
}

int main (int argc, char *argv[]) {
  std::vector<long long> galaxiesX;
  std::vector<long long> galaxiesY;

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

  long long xDifs = sum_pairs_difs(galaxiesX);
  long long yDifs = sum_pairs_difs(galaxiesY);

  std::cout << xDifs + yDifs << std::endl;

  return 0;
}
