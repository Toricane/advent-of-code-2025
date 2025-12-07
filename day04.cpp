// Day 4
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::string;
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

// compute the answer for Day 4 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   long long accessible = 0;
   for (unsigned i = 0; i < lines.size(); i++)
   {
      for (unsigned j = 0; j < lines[i].size(); j++)
      {
         if (lines[i][j] == '.')
         {
            continue;
         }
         int numAdj = 0;
         for (int x = j - 1; x <= static_cast<int>(j) + 1; x++)
         {
            for (int y = i - 1; y <= static_cast<int>(i) + 1; y++)
            {
               if (0 <= x && static_cast<unsigned>(x) < lines[i].size() && 0 <= y && static_cast<unsigned>(y) < lines.size())
               {
                  if (static_cast<unsigned>(x) == j && static_cast<unsigned>(y) == i)
                  {
                     continue;
                  }
                  if (lines[y][x] == '@')
                  {
                     numAdj++;
                  }
               }
            }
         }
         if (numAdj < 4)
         {
            accessible++;
         }
      }
   }
   return accessible;
}

// compute the answer for Day 4 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(vector<string> lines)
{
   long long accessible = 0;
   long long removed = 0;

   do
   {
      accessible = 0;
      vector<unsigned> xIndex;
      vector<unsigned> yIndex;

      for (unsigned i = 0; i < lines.size(); i++)
      {
         for (unsigned j = 0; j < lines[i].size(); j++)
         {
            if (lines[i][j] == '.')
            {
               continue;
            }
            int numAdj = 0;
            for (int x = j - 1; x <= static_cast<int>(j) + 1; x++)
            {
               for (int y = i - 1; y <= static_cast<int>(i) + 1; y++)
               {
                  if (0 <= x && static_cast<unsigned>(x) < lines[i].size() && 0 <= y && static_cast<unsigned>(y) < lines.size())
                  {
                     if (static_cast<unsigned>(x) == j && static_cast<unsigned>(y) == i)
                     {
                        continue;
                     }
                     if (lines[y][x] == '@')
                     {
                        numAdj++;
                     }
                  }
               }
            }
            if (numAdj < 4)
            {
               accessible++;
               xIndex.push_back(j);
               yIndex.push_back(i);
            }
         }
      }

      for (unsigned z = 0; z < xIndex.size(); z++)
      {
         lines[yIndex[z]][xIndex[z]] = '.';
         removed++;
      }
   } while (accessible > 0);

   return removed;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 4 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 04 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 04 - Part 2:\n"
       << part2(lines) << '\n';
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
