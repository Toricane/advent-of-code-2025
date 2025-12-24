// Day 12
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::string;
using std::vector;
using std::stringstream;
using std::sort;
using std::unique;

// load the raw puzzle input from the default data file
// preconditions:
//    data.txt is present in the working directory
// postconditions:
//    returns the contents of data.txt as an ordered list of strings
vector<string> parse_input()
{
   return read_lines();
}

struct Point {
   int r;
   int c;
};

bool operator<(const Point& a, const Point& b) {
   if (a.r != b.r) {
      return a.r < b.r;
   }
   return a.c < b.c;
}

bool operator==(const Point& a, const Point& b) {
   return a.r == b.r && a.c == b.c;
}

void normalize(vector<Point>& shape) {
   if (shape.empty()) {
      return;
   }

   int min_r = shape[0].r;
   int min_c = shape[0].c;

   for (const Point& p : shape) {
      if (p.r < min_r) min_r = p.r;
      if (p.c < min_c) min_c = p.c;
   }

   for (Point& p : shape) {
      p.r -= min_r;
      p.c -= min_c;
   }
   
   sort(shape.begin(), shape.end()); 
}

vector<Point> rotate(const vector<Point>& in) {
   vector<Point> out;
   for (const Point& p : in) {
      out.push_back(Point{p.c, -p.r});
   }
   normalize(out);
   return out;
}

vector<Point> flip(const vector<Point>& in) {
   vector<Point> out;
   for (const Point& p : in) {
      out.push_back(Point{p.r, -p.c});
   }
   normalize(out);
   return out;
}

vector<vector<Point>> get_variations(const vector<Point>& base_shape) {
   vector<vector<Point>> variations;
   vector<Point> current = base_shape;
   normalize(current);

   for (int i = 0; i < 4; ++i) {
      variations.push_back(current);
      variations.push_back(flip(current));
      current = rotate(current);
   }
   
   sort(variations.begin(), variations.end());
   variations.erase(unique(variations.begin(), variations.end()), variations.end());
   
   return variations;
}

bool fits(const vector<vector<bool>>& grid, const vector<Point>& shape, int r, int c) {
   int rows = grid.size();
   int cols = grid[0].size();

   for (const Point& p : shape) {
      int nr = r + p.r;
      int nc = c + p.c;

      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
         return false;
      }

      if (grid[nr][nc]) {
         return false;
      }
   }

   return true;
}

void toggle(vector<vector<bool>>& grid, const vector<Point>& shape, int r, int c, bool val) {
   for (const Point& p : shape) {
      grid[r + p.r][c + p.c] = val;
   }
}

bool solve_region(vector<vector<bool>>& grid,
                  const vector<int>& shapesNeeded,
                  int index,
                  const vector<vector<vector<Point>>>& all_variations,
                  int last_r = 0, int last_c = -1) {
   if (index >= static_cast<int>(shapesNeeded.size())) {
      return true;
   }

   int shapeID = shapesNeeded[index];

   int start_r = 0;
   int start_c = 0;
   
   if (index > 0 && shapesNeeded[index] == shapesNeeded[index - 1]) {
      start_r = last_r;
      start_c = last_c; 
   }

   const vector<vector<Point>>& variations = all_variations[shapeID];

   int rows = grid.size();
   int cols = grid[0].size();

   for (const vector<Point>& shape_var : variations) {
      for (int r = 0; r < rows; ++r) {
         int c_begin = (r == start_r) ? start_c : 0;
         for (int c = c_begin; c < cols; ++c) {
            if (fits(grid, shape_var, r, c)) {
               toggle(grid, shape_var, r, c, true);

               if (solve_region(grid, shapesNeeded, index + 1, all_variations, r, c)) {
                  return true;
               }

               toggle(grid, shape_var, r, c, false);
            }
         }
      }
   }
   return false;
}

// compute the answer for Day 12 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<vector<Point>> shapes;
   vector<Point> shape;
   int shapeNum = 0;
   int rowNum = 0;
   int totalRegionsFit = 0;
   static vector<vector<vector<Point>>> all_variations;

   for (string line : lines) {
      if (line.find(':') > 0 && line.find(':') < 3) {
         shapeNum = stoi(line.substr(0, line.find(':')));
         rowNum = 0;
         if (shapeNum != 0) {
            normalize(shape);
            shapes.push_back(shape);
            shape.clear();
         }
      } else if (line.find(':') == string::npos && !line.empty()) {
         for (int i = 0; i < static_cast<int>(line.length()); i++) {
            if (line[i] == '#') {
               shape.push_back(Point{rowNum, i});
            }
         }
         rowNum++;
      } else if (line.find('x') != string::npos) {
         // cout << line << '\n';

         if (!shape.empty()) {
            normalize(shape);
            shapes.push_back(shape);
            shape.clear();
         }

         int width = stoi(line.substr(0, line.find('x')));
         int height = stoi(line.substr(line.find('x') + 1, line.find(':') - line.find('x') - 1));

         stringstream ss(line.substr(line.find(':') + 2));
         vector<int> shapesNeeded;
         int numShapes, shapeID = 0;

         if (all_variations.empty() && !shapes.empty()) {
            for (const vector<Point>& s : shapes) {
               all_variations.push_back(get_variations(s));
            }
         }

         vector<vector<bool>> grid(height, vector<bool>(width, false));

         while (ss >> numShapes) {
            for (int i = 0; i < numShapes; i++) {
               shapesNeeded.push_back(shapeID);
            }
            shapeID++;
         }

         int total_present_area = 0;
         for (int id : shapesNeeded) {
            total_present_area += shapes[id].size(); 
         }

         if (total_present_area > width * height) {
            continue;
         }

         sort(shapesNeeded.begin(), shapesNeeded.end(), [&](int a, int b) {
            if (shapes[a].size() != shapes[b].size()) {
               return shapes[a].size() > shapes[b].size();
            }
            return a < b;
         });

         if (solve_region(grid, shapesNeeded, 0, all_variations)) {
            totalRegionsFit++;
         }
      }
   }

   return totalRegionsFit;
}

// compute the answer for Day 12 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   return 0;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 12 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 12 - Part 1:\n" << part1(lines) << '\n';
   out << "Day 12 - Part 2:\n" << part2(lines) << '\n';
}

// program entry point delegating to solve using standard output
// preconditions:
//    standard output stream is available
// postconditions:
//    returns 0 after solve completes
int main()
{
   solve(cout);
   return 0;
}
