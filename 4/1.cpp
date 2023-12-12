#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main (int argc, char *argv[]) {
  long long total = 0;


  for (std::string line; std::getline(std::cin, line);) {
    std::set<int> winning;
    std::set<int> have;

    std::stringstream ls(line);

    std::string token;
    int card;
    char colon;

    ls >> token; // Discard 'Card'
    ls >> card;  // Discard 'i'
    ls >> colon;  // Discard ':'
    
    getline(ls, token, ' '); // Get first token
    while (token.compare("|") != 0) {
      if (token.size() > 0) {
        int i = std::stoi(token);
        winning.insert(i); 
      }
      getline(ls, token, ' '); // get following tokens
    }

    while(std::getline(ls, token, ' ')) {
      if (token.size() > 0) {
        int i = std::stoi(token);
        have.insert(i);
      }
    }

    std::set<int> intersect;
    std::set_intersection(winning.begin(), winning.end(), have.begin(), have.end(), std::inserter(intersect, intersect.begin()));

    int matches = intersect.size();
    if (matches > 0) {
      total += 1 << (matches - 1);
    }
  }


  std::cout << total << std::endl;

  return 0;
}
















