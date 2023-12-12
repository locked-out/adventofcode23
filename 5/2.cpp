#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <cstring>
#include <map>

typedef struct map {
  long long src;
  long long dest;
  long long range;
} map_t;

inline bool operator<(const map &a, const map &b) {
  if (a.src != b.src) return a.src < b.src;
  if (a.range != b.range) return a.range < b.range;
  return a.dest < b.dest;
}

typedef struct range {
  long long start;
  long long range;
} range_t;

inline bool operator<(const range &a, const range &b) {
  if (a.start != b.start) return a.start < b.start;
  return a.range < b.range;
}

int main (int argc, char *argv[]) {
  long long nseeds;
  std::cin >> nseeds;
  nseeds /= 2;
  
  std::vector<range_t> seeds(nseeds);
  for (long long i = 0; i < nseeds; i++) {
    std::cin >> seeds[i].start >> seeds[i].range;
  }

  long long nmaps;
  std::cin >> nmaps;

  for (long long i = 0; i < nmaps; i++) {
    printf("map %llu:\n", i+1);
    long long mapsize;
    std::cin >> mapsize;

    std::map<long long, map_t> maps;
    for (long long j = 0; j < mapsize; j++) {
      map_t m;
      std::cin >> m.dest >> m.src >> m.range;
      maps[m.src] = m;
    }
   
    std::vector<range_t> new_seeds;

    // Update seeds
    while (seeds.size() > 0) {
      range_t seed = seeds.back();
      seeds.pop_back();

      long long seedend = seed.start + seed.range;
      
      // Get first element greater or equal to seedend
      auto relevant_map = maps.lower_bound(seedend);
      
      // If iterator points to begining, all maps are larger than seedend
      if (relevant_map == maps.begin()) {
        new_seeds.push_back(seed);
        continue;
      }

      // Now get the last map smaller than seedend
      relevant_map--;
      map_t mapping = relevant_map->second;

      long long mapend = mapping.src + mapping.range;
      if (mapend <= seed.start) {
        new_seeds.push_back(seed);
        continue;
      }
      // Now mapping is guaranteed to overlap with seed

      // Trim outer left
      if (seed.start < mapping.src) {
        range_t outer_left;
        outer_left.start = seed.start;
        outer_left.range = mapping.src - seed.start;


        seeds.push_back(outer_left);
        seed.start = mapping.src;
        seed.range -= outer_left.range;
      }

      // Trim outer right
      if (seedend > mapend) {
        range_t outer_right;
        outer_right.start = mapend;
        outer_right.range = seedend - mapend;
        seeds.push_back(outer_right);
        seedend = mapend;
        seed.range = seedend - seed.start;
      }

      // Map this range
      seed.start = seed.start - mapping.src + mapping.dest;
      new_seeds.push_back(seed);
    }

    seeds = new_seeds;
    std::sort(seeds.begin(), seeds.end());
    for (auto seed : seeds) printf("[%llu, %llu) ", seed.start, seed.start + seed.range);
    std::cout << "\n"; 
  }

  long long smallest_seed = UINT32_MAX;
  for (range_t seed : seeds) {
    if (seed.start < smallest_seed) smallest_seed = seed.start;
  }

  printf("%llu\n", smallest_seed);

  return 0;
}
