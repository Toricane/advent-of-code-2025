// Day 1
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

// compute the answer for Day 1 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   int dial = 50;
   long long num_0 = 0;
   int sign, num;

   for (string turn : lines)
   {
      if ((turn.size() < 2) || (turn[0] != 'L' && turn[0] != 'R'))
      {
         break;
      }

      if (turn[0] == 'L')
      {
         sign = -1;
      }
      else
      {
         sign = 1;
      }

      num = stoi(turn.substr(1));

      dial += (sign * num) % 100;
      dial %= 100;

      if (dial < 0)
      {
         dial = 100 + dial;
      }

      if (dial == 0)
      {
         num_0++;
      }
   }

   return num_0;
}

// compute the answer for Day 1 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   int dial = 50;
   long long num_0 = 0;
   int sign, num;

   for (string turn : lines)
   {
      if ((turn.size() < 2) || (turn[0] != 'L' && turn[0] != 'R'))
      {
         break;
      }

      num = stoi(turn.substr(1));
      num_0 += num / 100;

      if (turn[0] == 'L')
      {
         sign = -1;

         if (dial - (num % 100) <= 0 && dial != 0)
         {
            num_0++;
         }
      }
      else
      {
         sign = 1;
         
         if (dial + (num % 100) > 99)
         {
            num_0++;
         }
      }

      dial += (sign * num) % 100;
      dial %= 100;

      if (dial < 0)
      {
         dial = 100 + dial;
      }
   }

   return num_0;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 1 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 01 - Part 1: " << part1(lines) << '\n';
   out << "Day 01 - Part 2: " << part2(lines) << '\n';
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
