// Day 3
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cmath>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::pow;
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

// compute the answer for Day 3 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   long long total = 0;
   int max1 = 0;
   int max2 = 0;
   unsigned index1;
   int digit;

   for (string bank : lines)
   {
      if (bank.size() == 0)
      {
         continue;
      }
      for (unsigned i = 0; i < bank.size() - 1; i++)
      {
         digit = bank[i] - '0';
         if (digit > max1)
         {
            max1 = digit;
            index1 = i;
         }
      }
      for (unsigned i = index1 + 1; i < bank.size(); i++)
      {
         digit = bank[i] - '0';
         if (digit > max2 && i != index1)
         {
            max2 = digit;
         }
      }

      total += max1 * 10 + max2;
      max1 = 0;
      max2 = 0;
   }
   return total;
}

// compute the answer for Day 3 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   long long total = 0;
   int digit;

   for (string bank : lines)
   {
      if (bank.size() == 0)
      {
         continue;
      }

      int index = 0;

      for (int place = 11; place >= 0; place--)
      {
         int max = 0;

         for (unsigned i = index; i < bank.size() - place; i++)
         {
            digit = bank[i] - '0';

            if (digit > max)
            {
               max = digit;
               index = i;
            }
         }

         total += max * pow(10, place);
         index++;
      }
   }
   return total;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 3 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 03 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 03 - Part 2:\n"
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
