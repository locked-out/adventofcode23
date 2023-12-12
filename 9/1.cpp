#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int extrapolate(std::vector<int> &v) {
  std::vector<int> down_diag;
  int up_diag;

  int i = 1;
  int n = v.size() - 1;
  down_diag.push_back(v.back());
  up_diag = v.back();

  while (down_diag.back() != 0) {
    int last_val = down_diag[0];
    down_diag[0] = v[n-i];

    for (int j = 1; j < down_diag.size(); j++) {
      int dif = last_val - down_diag[j-1];
      last_val = down_diag[j];
      down_diag[j] = dif;
    }
    down_diag.push_back(last_val - down_diag.back());
    up_diag += down_diag.back();

    i++;
  }

  return up_diag;
}

int main (int argc, char *argv[]) {
  std::string line;

  int ends = 0;

  while (std::getline(std::cin, line)) {
    std::stringstream line_stream(line);
    
    std::vector<int> seq;
    int n;
    while(line_stream >> n) {
      seq.push_back(n);
    }

    ends += extrapolate(seq);
  }

  std::cout << ends << std::endl;

  return 0;
}
