#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main (int argc, char *argv[]) {
  long long total = 0;

  int cardno = 0;
  int ncopies = 1;

  // When we win n cards, incease ncopies and place <cardno + n, ncopies won> in the queue
  //  so we know when to decrement again and by how much
  std::priority_queue<
    std::pair<int, int>, 
    std::vector<std::pair<int, int>>, 
    std::greater<std::pair<int, int>>
  > win_ends; 

  for (std::string line; std::getline(std::cin, line);) {
    while (win_ends.size() > 0 && win_ends.top().first < cardno) {
      ncopies -= win_ends.top().second;
      win_ends.pop();
    }

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

    total += ncopies;

    int matches = intersect.size();
    if (matches > 0) {
      win_ends.push(std::make_pair(cardno+matches, ncopies));
      ncopies *= 2;
    }

    cardno++;
  }


  std::cout << total << std::endl;

  return 0;
}
















