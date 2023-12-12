#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>

#define UP 1
#define DOWN 2
#define RIGHT 4
#define LEFT 8

#define LOOP 16
#define VISITED 32

#define OPPOSITE(dir) (((dir >> 1) & 0b0101) | ((dir & 0b0101) << 1))


#define MAXCOLS 140 
#define MAXROWS 140

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}     

std::string pretty(char c) {
  switch (c) {
    case '|':
      return "│";
    case '-':
      return "─";
    case 'L':
      return "└";
    case 'J':
      return "┘";
    case '7':
      return "┐";
    case 'F':
      return "┌";
    default:
      return "S";
  }
}

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

int get_path_len(int grid[MAXCOLS+1][MAXROWS+1], std::pair<int, int> start, const std::pair<int, int> goal, int last_dir) {
  int len = 1;
  
  int first_dir = last_dir;

  while (start != goal) {
    grid[start.first][start.second] |= LOOP;
    int opp_dir = OPPOSITE(last_dir);

    int next_dir = 0b1111 & (grid[start.first][start.second] & (~opp_dir));
    std::pair<int, int> next_offset = direction_to_offset(next_dir);

    start = start + next_offset;
    last_dir = next_dir;
    len++;
  }

  grid[goal.first][goal.second] = first_dir | OPPOSITE(last_dir);
  grid[goal.first][goal.second] |= LOOP; 

  return len;
}



int main (int argc, char *argv[]) {
  auto grid = new int[MAXCOLS+1][MAXROWS+1]; 
  auto chars = new char[MAXCOLS+1][MAXROWS+1];

  std::pair<int, int> start;

  int row = 0;
  int cols;
  for (std::string line; std::getline(std::cin, line);) {
    std::stringstream line_stream(line);

    int col = 0;
    for (char c; line_stream >> c;){
      chars[row][col] = c;
      if (c == 'S') {
        start = std::make_pair(row, col);
      } else {
        int connections = get_connections(c);
        grid[row][col] = connections;
      } 
      col++;
    }
    cols = col;
    row++;
  }

  int rows = row;
  int path_len = 0;

  for (int dir = 1; dir <= 8; dir = dir << 1) {
    std::pair<int, int> offset = direction_to_offset(dir);

    std::pair<int, int> adj = start + offset;
     
    int opp_dir = OPPOSITE(dir);

    if (grid[adj.first][adj.second] & opp_dir) {
      path_len = get_path_len(grid, adj, start, dir);
      break;
    }
  }

  // Flood fill, grid[i][j].VISITED is if the top left corner of cell i,j is visited

  std::pair<int, int> offsets[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  std::pair<int, int> blocking_offsets[4] = {{0, 0}, {-1, 0}, {0, 0}, {0, -1}};
  int blocking_connections[4] = {LEFT, LEFT, UP, UP};

  int reachable = 0;

  std::queue<std::pair<int, int>> q;
  q.push(std::make_pair(0, 0));

  while (q.size() > 0) {
    std::pair<int, int> pos = q.front();
    q.pop();

    if (grid[pos.first][pos.second] & VISITED) {
      continue;
    }

    grid[pos.first][pos.second] |= VISITED;
    if (!(grid[pos.first][pos.second] & LOOP)) {
      reachable++;
    }

    for (int i = 0; i < 4; i++) {
      std::pair<int, int> adj = pos + offsets[i];
      if (adj.first >= 0 && adj.first <= rows && adj.second >= 0 && adj.second <= cols) {
        std::pair<int, int> blocking_pos = pos + blocking_offsets[i];
        int blocking_status = grid[blocking_pos.first][blocking_pos.second];
        if (!(blocking_status & LOOP && blocking_status & blocking_connections[i])) {
          q.push(adj);
        }
      }
    }
  }

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] & LOOP) {
        std::cout << pretty(chars[row][col]);
      } else if (grid[row][col] & VISITED) {
        std::cout << "O";
      } else {
        std::cout << "I";
      }
    }
    printf("\n");
  }

  // Subtract bottom row and right column size
  int total = rows * cols;
  int outside = reachable - rows - cols - 1;
  int inside = total - outside - path_len;
  std::cout << inside << std::endl; 
  return 0;
}

