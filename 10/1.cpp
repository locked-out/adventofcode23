#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#define UP 1
#define DOWN 2
#define RIGHT 4
#define LEFT 8


#define OPPOSITE(dir) (((dir >> 1) & 0b0101) | ((dir & 0b0101) << 1))


#define MAXCOLS 140 
#define MAXROWS 140 

int get_connections(const char c) {
  switch (c) {
    case '|':
      return UP | DOWN;
    case '-':
      return LEFT | RIGHT;
    case 'L':
      return UP | RIGHT;
    case 'J':
      return UP | LEFT;
    case '7':
      return DOWN | LEFT;
    case 'F':
      return DOWN | RIGHT;
    default:
      return 0;
  }
}

inline std::pair<int, int> direction_to_offset(int direction) {
  switch (direction) {
    case UP:
      return std::make_pair(-1, 0);
    case RIGHT:
      return std::make_pair(0, 1);
    case DOWN:
      return std::make_pair(1, 0);
    case LEFT:
      return std::make_pair(0, -1);
  }
  return std::make_pair(0, 0);
}

int get_path_len(const int grid[MAXCOLS][MAXROWS], std::pair<int, int> start, const std::pair<int, int> goal, int last_dir) {
  int len = 1;
  while (start != goal) {
    int opp_dir = OPPOSITE(last_dir);

    int next_dir = grid[start.first][start.second] & (~opp_dir);
    std::pair<int, int> next_offset = direction_to_offset(next_dir);

    start.first += next_offset.first;
    start.second += next_offset.second;
    last_dir = next_dir;
    len++;
  }

  return len;
}

int main (int argc, char *argv[]) {
  auto grid = new int[MAXCOLS][MAXROWS]; 

  std::pair<int, int> start;

  int row = 0;
  for (std::string line; std::getline(std::cin, line);) {
    std::stringstream line_stream(line);

    int col = 0;
    for (char c; line_stream >> c;){
      if (c == 'S') {
        start = std::make_pair(row, col);
      } else {
        int connections = get_connections(c);
        grid[row][col] = connections;
      } 
      col++;
    }
    row++;
  }

  for (int dir = 1; dir <= 8; dir = dir << 1) {
    std::pair<int, int> offset = direction_to_offset(dir);

    std::pair<int, int> adj = std::make_pair(start.first+offset.first, start.second+offset.second);
     
    int opp_dir = OPPOSITE(dir);

    if (grid[adj.first][adj.second] & opp_dir) {
      std::cout << get_path_len(grid, adj, start, dir)/2 << std::endl;
      break;
    }
  }

  return 0;
}

