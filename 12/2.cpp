#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#define DOT 0
#define HASH 1

#define MAX_HASHES (17*5)

// vector at i is true iff the i_th hash placed is at the end of a group
// vector[0] is always true for convienience
std::vector<bool> get_group_ends(int n_hashes, const std::vector<int> &groups) {
  std::vector<bool> is_group_end(n_hashes+1);
  is_group_end[0] = true;

  int group_end = 0;
  for (int group : groups) {
    group_end += group;
    is_group_end[group_end] = true;
  }
  
  return is_group_end;
}

long long get_possibilities(const std::string &str, const std::vector<int> &groups) {
  int n_hashes = std::accumulate(groups.begin(), groups.end(), 0);  

  std::vector<bool> is_group_end = get_group_ends(n_hashes, groups);

  int n = str.size();

  // dp[i][hashes_placed][char] = possible ways of placing a {char} at position i 
  //   where:
  //     i = 1 index location in the string you are trying to place a character at 
  //     hashes_placed = number of hashes placed already (excluding current attempt)
  //     char = character you are trying to place = DOT or HASH
  //
  auto dp = new long long[n+1][MAX_HASHES+1][2];

  // Treat 'before start of array' as a dot with no hashes placed
  dp[0][0][DOT] = 1;

  for (int i = 1; i <= n; i++) {
    if (str[i-1] != '.') {
      // Possibilities for hash
      for (int hashes_placed = 1; hashes_placed <= std::min(i, n_hashes); hashes_placed++) {
        if (is_group_end[hashes_placed - 1]) {
          // If start of new group
          // Must follow a dot
          dp[i][hashes_placed][HASH] = dp[i-1][hashes_placed-1][DOT];
        } else {
          // Must follow a hash
          dp[i][hashes_placed][HASH] = dp[i-1][hashes_placed-1][HASH];
        }
      }
    }

    if (str[i-1] != '#') {
      // Possibilities for dot
      for (int hashes_placed = 0; hashes_placed <= std::min(i-1, n_hashes); hashes_placed++) {
        if (is_group_end[hashes_placed]) {
          // If end of a group
          // We can safely place a dot 
          dp[i][hashes_placed][DOT] = dp[i-1][hashes_placed][DOT] + dp[i-1][hashes_placed][HASH];
        } else {
          // We are not at the end of a group, therefore we can't place a dot!
          // Leave dp as 0 at this position
        }
      }
    }
  }

  return dp[n][n_hashes][DOT] + dp[n][n_hashes][HASH];
}


int main (int argc, char *argv[]) {

  long long sum_possible = 0;

  for (std::string line; std::getline(std::cin, line);) {
    std::stringstream line_stream(line);

    std::string spring_row;
    line_stream >> spring_row;

    std::string expanded_spring_row(spring_row);
    for (int i = 0; i < 4; i++) {
      expanded_spring_row += '?';
      expanded_spring_row += spring_row;
    }

    std::string rest;
    line_stream >> rest;

    std::vector<int> groups;

    std::stringstream group_stream(rest);
    for (std::string tok; std::getline(group_stream, tok, ',');) {
      groups.push_back(std::stoi(tok));
    }

    std::vector<int> expanded_groups(groups.size());
    for (int i = 0; i < 5; i++){
      for (auto group : groups) {
        expanded_groups.push_back(group);
      }
    }
    auto possibilities = get_possibilities(expanded_spring_row, expanded_groups);
    sum_possible += possibilities; 
  }

  std::cout << sum_possible << std::endl;
  return 0;
}
