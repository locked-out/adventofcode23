#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

int get_depth(const std::vector<int> &v) {
  std::vector<int> down_diag;

  int i = 1;
  int n = v.size() - 1;
  down_diag.push_back(v.back());

  while (down_diag.back() != 0) {
    int last_val = down_diag[0];
    down_diag[0] = v[n-i];

    for (int j = 1; j < down_diag.size(); j++) {
      int dif = last_val - down_diag[j-1];
      last_val = down_diag[j];
      down_diag[j] = dif;
    }
    down_diag.push_back(last_val - down_diag.back());

    i++;
  }

  return i;
}
int extrapolate(const std::vector<int> &v) {
  std::vector<int> up_diag;
  std::vector<int> down_diag;

  int i = 1;
  int depth = get_depth(v);
  up_diag.push_back(v[0]);
  down_diag.push_back(v[0]);

  while (i < depth) {
    int last_val = up_diag[0];
    up_diag[0] = v[i];

    for (int j = 1; j < up_diag.size(); j++) {
      int dif = up_diag[j-1] - last_val;
      last_val = up_diag[j];
      up_diag[j] = dif;
    }
    up_diag.push_back(up_diag.back() - last_val);
    down_diag.push_back(up_diag.back());

    i++;
  }

  int ans = 0;
  for (i = down_diag.size() - 2; i >= 0; i--) {
    ans = down_diag[i] - ans;
  }

  return ans;
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
