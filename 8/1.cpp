#include <iostream>
#include <istream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <thread>
#include <utility>
#include <vector>

u_int get_id(std::map<std::string, int> &name_to_id, const std::string ref) {
  if (name_to_id.find(ref) == name_to_id.end()) 
  {
    int size = name_to_id.size();
    name_to_id[ref] = size;
  }
  return name_to_id[ref];
}

int main (int argc, char *argv[]) {
  std::string lrstring;
  std::cin >> lrstring;

  std::cin >> std::ws; // Skip whitespace?
  

  std::vector<std::pair<int, int>> graph;

  // Give each named location an id the quick access
  std::map<std::string, int> name_to_id; 

  for (std::string line; std::getline(std::cin, line);) {
    std::stringstream ls(line);

    std::string token;
    ls >> token; // Get ABC
    u_int from = get_id(name_to_id, token);


    ls >> token; // Discard =
    ls >> token; // get (ABC,
    token = token.substr(1, 3); // Trim to ABC
    u_int left = get_id(name_to_id, token);

    ls >> token; // Get ABC)
    token = token.substr(0, 3); // Trim to ABC
    u_int right = get_id(name_to_id, token);

    if (from >= graph.size()) {
      graph.resize(from+1);
    }
    graph[from] = std::make_pair(left, right);
  }

  u_int start = name_to_id["AAA"];
  u_int end = name_to_id["ZZZ"];

  u_int curr = start;
  u_int steps = 0;
  while (curr != end) {

    switch (lrstring[steps % lrstring.size()]) {
      case 'L':
        curr = graph[curr].first;
        break;
      case 'R':
        curr = graph[curr].second;
        break;
    }
    steps++;
  }

  std::cout << steps << std::endl;

  return 0;
}
