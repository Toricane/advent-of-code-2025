// Day 7
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

// compute the answer for Day 7 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(vector<string> &manifold)
{
   long long numSplits = 0;

   for (unsigned i = 0; i < manifold.size(); i++)
   {
      string line = manifold[i];

      if (line.size() == 0)
      {
         continue;
      }

      if (line.find('S') != string::npos)
      {
         manifold[i + 1][line.find('S')] = '|';
         continue;
      }

      for (unsigned j = 0; j < line.size(); j++)
      {
         if (line[j] == '^' && manifold[i - 1][j] == '|')
         {
            manifold[i][j - 1] = '|';
            manifold[i][j + 1] = '|';
            numSplits++;
            j++;
         }
         else if (manifold[i - 1][j] == '|')
         {
            manifold[i][j] = '|';
         }
      }
   }

   return numSplits;
}

// compute the answer for Day 7 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(vector<string> &manifold)
{
   // uses Part 1's updated manifold!

   vector<long long> plinkos(manifold[0].size(), 0);
   plinkos[manifold[0].find('S')] = 1;

   for (unsigned line2 = 2; line2 < manifold.size(); line2++)
   {
      vector<long long> nextPlinkos(manifold[0].size(), 0);

      for (unsigned col = 0; col < plinkos.size(); col++)
      {
         long long currentPlinkos = plinkos[col];

         if (col < manifold[line2].size() && manifold[line2][col] == '^')
         {
            if (col > 0)
            {
               nextPlinkos[col - 1] += currentPlinkos;
            }
            if (col + 1 < nextPlinkos.size())
            {
               nextPlinkos[col + 1] += currentPlinkos;
            }
         }
         else
         {
            nextPlinkos[col] += currentPlinkos;
         }
      }
      plinkos = nextPlinkos;
   }

   long long totalPlinkos = 0;

   for (long long numPlinkos : plinkos)
   {
      totalPlinkos += numPlinkos;
   }

   return totalPlinkos;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 7 answers to the stream
void solve(ostream &out)
{
   vector<string> lines = parse_input();
   out << "Day 07 - Part 1:\n"
       << part1(lines) << '\n'; // lines is modified by part1(lines)
   out << "Day 07 - Part 2:\n"
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
