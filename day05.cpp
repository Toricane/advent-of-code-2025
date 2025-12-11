// Day 5
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
using std::cout;
using std::max;
using std::ostream;
using std::sort, std::binary_search;
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

struct Range
{
   long long min;
   long long max;

   bool operator<(const Range &range2) const
   {
      return min < range2.min;
   }
};

// compute the answer for Day 5 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<Range> ranges;
   vector<long long> ingredients;
   bool blank = false;

   for (const string line : lines)
   {
      if (line.size() == 0)
      {
         blank = true;
      }
      else if (!blank)
      {
         Range range;
         stringstream ss(line);
         char temp;

         ss >> range.min >> temp >> range.max;
         ranges.push_back(range);
      }
      else
      {
         ingredients.push_back(stoll(line));
      }
   }

   sort(ranges.begin(), ranges.end());

   vector<Range> mergedRanges;
   mergedRanges.push_back(ranges[0]);

   for (unsigned i = 1; i < ranges.size(); i++)
   {
      Range &current = ranges[i];
      Range &last = mergedRanges.back();

      if (current.min <= last.max + 1)
      {
         last.max = max(last.max, current.max);
      }
      else
      {
         mergedRanges.push_back(current);
      }
   }

   long long fresh = 0;

   for (const long long i : ingredients)
   {
      for (const Range range : mergedRanges)
      {
         if (range.min <= i && i <= range.max)
         {
            fresh++;
            break;
         }
      }
   }

   return fresh;
}

// compute the answer for Day 5 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   vector<Range> ranges;

   for (const string line : lines)
   {
      if (line.size() == 0)
      {
         break;
      }
      else
      {
         Range range;
         stringstream ss(line);
         char temp;

         ss >> range.min >> temp >> range.max;
         ranges.push_back(range);
      }
   }

   sort(ranges.begin(), ranges.end());

   vector<Range> mergedRanges;
   mergedRanges.push_back(ranges[0]);

   for (unsigned i = 1; i < ranges.size(); i++)
   {
      Range &current = ranges[i];
      Range &last = mergedRanges.back();

      if (current.min <= last.max + 1)
      {
         last.max = max(last.max, current.max);
      }
      else
      {
         mergedRanges.push_back(current);
      }
   }

   long long fresh = 0;

   for (const Range range : mergedRanges)
   {
      fresh += range.max - range.min + 1;
   }

   return fresh;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 5 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 05 - Part 1: " << part1(lines) << '\n';
   out << "Day 05 - Part 2: " << part2(lines) << '\n';
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
