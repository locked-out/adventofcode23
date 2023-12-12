#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <cstring>

typedef struct map {
  u_int src;
  u_int dest;
  u_int range;
} map_t;

int main (int argc, char *argv[]) {
  u_int nseeds;
  std::cin >> nseeds;
  
  std::vector<u_int> seeds(nseeds);
  for (u_int i = 0; i < nseeds; i++) std::cin >> seeds[i];

  u_int nmaps;
  std::cin >> nmaps;

  for (u_int i = 0; i < nmaps; i++) {
    u_int mapsize;
    std::cin >> mapsize;

    std::vector<map_t> maps(mapsize);
    for (u_int j = 0; j < mapsize; j++) {
      std::cin >> maps[j].dest >> maps[j].src >> maps[j].range;
    }
   
    // Update seeds
    for (u_int j = 0; j < nseeds; j++) {
      u_int seed = seeds[j];

      for (map_t mapping : maps) {
        if (seed >= mapping.src && seed < mapping.src + mapping.range) {
          seeds[j] = seed - mapping.src + mapping.dest;
          break;
        }
      } 
    }

    for (u_int seed : seeds) std::cout << seed << ' ';
    std::cout << '\n'; 
  }

  std::cout << *std::min_element(seeds.begin(), seeds.end()) << '\n';

  return 0;
}
