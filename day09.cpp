// Day 9
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using advent::read_lines;
using std::abs, std::min, std::max;
using std::binary_search;
using std::cout;
using std::ostream;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;

// load the raw puzzle input from the default data file
// preconditions:
//    data.txt is present in the working directory
// postconditions:
//    returns the contents of data.txt as an ordered list of strings
vector<string> parse_input()
{
   return read_lines();
}

struct Tile
{
   long long x;
   long long y;
};

long long calculateArea(Tile i, Tile j)
{
   return (abs(i.x - j.x) + 1) * (abs(i.y - j.y) + 1);
}

// compute the answer for Day 9 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<Tile> grid;
   char temp;

   for (string line : lines)
   {
      if (line.size() == 0)
      {
         continue;
      }

      Tile tile;
      stringstream ss(line);
      ss >> tile.x >> temp >> tile.y;
      grid.push_back(tile);
   }

   long long maxArea = 0;

   for (unsigned i = 0; i < grid.size(); i++)
   {
      for (unsigned j = i + 1; j < grid.size(); j++)
      {
         long long area = calculateArea(grid[i], grid[j]);
         if (area > maxArea)
         {
            maxArea = area;
         }
      }
   }

   return maxArea;
}

bool pointInside(double x, double y, const vector<Tile> &polygon)
{
   bool inside = false;

   for (unsigned i = 0; i < polygon.size(); i++)
   {
      Tile edge1 = polygon[i];
      Tile edge2 = polygon[(i + 1) % polygon.size()];

      if (edge1.y == edge2.y)
      {
         continue;
      }

      if (y > min(edge1.y, edge2.y) && y <= max(edge1.y, edge2.y))
      {
         if (x < edge1.x)
         {
            inside = !inside;
         }
      }
   }

   return inside;
}

bool wallCutsRect(long long minX, long long maxX, long long minY, long long maxY, const vector<Tile> &polygon)
{
   for (unsigned i = 0; i < polygon.size(); i++)
   {
      Tile edge1 = polygon[i];
      Tile edge2 = polygon[(i + 1) % polygon.size()];

      if (edge1.x == edge2.x)
      {
         if (edge1.x > minX && edge1.x < maxX)
         {
            long long wallMinY = min(edge1.y, edge2.y);
            long long wallMaxY = max(edge1.y, edge2.y);

            if (max(minY, wallMinY) < min(maxY, wallMaxY))
            {
               return true;
            }
         }
      }
      else if (edge1.y == edge2.y)
      {
         if (edge1.y > minY && edge1.y < maxY)
         {
            long long wallMinX = min(edge1.x, edge2.x);
            long long wallMaxX = max(edge1.x, edge2.x);

            if (max(minX, wallMinX) < min(maxX, wallMaxX))
            {
               return true;
            }
         }
      }
   }

   return false;
}

bool withinPolygon(const vector<Tile> &polygon, Tile i, Tile j)
{
   long long minX = min(i.x, j.x);
   long long maxX = max(i.x, j.x);
   long long minY = min(i.y, j.y);
   long long maxY = max(i.y, j.y);

   double midX = (minX + maxX) / 2.0;
   double midY = (minY + maxY) / 2.0;
   if (!pointInside(midX, midY, polygon))
   {
      return false;
   }

   if (wallCutsRect(minX, maxX, minY, maxY, polygon))
   {
      return false;
   }

   return true;
}

// compute the answer for Day 9 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   vector<Tile> polygon;
   char temp;

   for (string line : lines)
   {
      if (line.size() == 0)
      {
         continue;
      }

      Tile tile;
      stringstream ss(line);
      ss >> tile.x >> temp >> tile.y;
      polygon.push_back(tile);
   }

   long long maxArea = 0;

   for (unsigned i = 0; i < polygon.size(); i++)
   {
      for (unsigned j = i + 1; j < polygon.size(); j++)
      {
         if (!withinPolygon(polygon, polygon[i], polygon[j]))
         {
            continue;
         }
         long long area = calculateArea(polygon[i], polygon[j]);
         if (area > maxArea)
         {
            maxArea = area;
         }
      }
   }

   return maxArea;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 9 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 09 - Part 1: " << part1(lines) << '\n';
   out << "Day 09 - Part 2: " << part2(lines) << '\n';
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
