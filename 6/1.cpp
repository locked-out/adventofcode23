#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define EPSILON (1e-10)


typedef struct race {
  int time;
  int distance;
} race_t;

int ways_to_beat_race(const race_t race) {
  // Function for distance travelled is: 
  //   dist(hold_time) = hold_time * (total_time - hold_time)
  // Solve for 
  //   dist(hold_time) = distance
  // Expanded and rearranged is
  //   0 = hold_time^2 - total_time * hold_time + distance
  // Solving for hold_time, using quadratic formula
  //   determinant = total_time^2 - 4 * distance
  //   t = (total_time +- sqrt(determinant))/2
  
  long long determinant = race.time * race.time - 4 * race.distance;
  if (determinant <= 0) return 0;
  
  double sqrtdeterm = std::sqrt(determinant);

  double tsmall = (race.time - sqrtdeterm) / 2;
  double tlarge = (race.time + sqrtdeterm) / 2;

  int lower_bound = std::ceil(tsmall);
  int upper_bound = std::floor(tlarge);

  if (lower_bound - tsmall < EPSILON) lower_bound++;
  if (tlarge - upper_bound < EPSILON) upper_bound--;

  return upper_bound - lower_bound + 1;
}

int main (int argc, char *argv[]) {
  std::vector<race_t> races;

  std::string token;

  // Skip 'Time:' token
  std::cin >> token;

  // Loop through each time
  for (std::cin >> token; token.compare("Distance:") != 0; std::cin >> token) {
    race_t r;
    r.time = std::stoi(token);
    races.push_back(r);
  }
  
  for (race_t &race : races) {
    std::cin >> race.distance;
  }

  int product = 1;

  for (race_t race : races) {
    product *= ways_to_beat_race(race);
  } 
  
  std::cout << product << '\n';

  return 0;
}
