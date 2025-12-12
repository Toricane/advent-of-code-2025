// Day 6
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::remove_if;
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
   vector<string> lines = read_lines();

   while (lines.back().size() == 0)
   {
      lines.pop_back();
   }

   return lines;
}

// compute the answer for Day 6 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<vector<long long>> problems;
   vector<char> operations;

   for (unsigned i = 0; i < lines.size() - 1; i++)
   {
      string line = lines[i];

      if (line.size() == 0)
      {
         continue;
      }

      stringstream ss(line);
      vector<long long> problem;
      long long num;

      while (ss >> num)
      {
         problem.push_back(num);
      }

      problems.push_back(problem);
   }

   string last = lines.back();
   last.erase(remove_if(last.begin(), last.end(), isspace), last.end());

   for (const char &operation : last)
   {
      operations.push_back(operation);
   }

   long long total = 0;
   long long subtotal = 0;

   for (unsigned problemNum = 0; problemNum < operations.size(); problemNum++)
   {
      char operation = operations[problemNum];

      if (operation == '+')
      {
         subtotal = 0;
      }
      else if (operation == '*')
      {
         subtotal = 1;
      }

      for (const vector<long long> &problem : problems)
      {
         if (operation == '+')
         {
            subtotal += problem[problemNum];
         }
         else if (operation == '*')
         {
            subtotal *= problem[problemNum];
         }
      }

      total += subtotal;
   }

   return total;
}

// compute the answer for Day 6 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   char operation = ' ';
   long long num = 0;
   vector<long long> numbers;
   long long subtotal = 0;
   long long total = 0;

   for (unsigned i = 0; i < lines[0].size(); i++)
   {
      if (lines.back()[i] != ' ')
      {
         operation = lines.back()[i];
         total += subtotal;

         if (operation == '+')
         {
            subtotal = 0;
         }
         else if (operation == '*')
         {
            subtotal = 1;
         }
      }

      num = 0;

      for (unsigned j = 0; j < lines.size() - 1; j++)
      {
         if (lines[j][i] == ' ')
         {
            continue;
         }
         num *= 10;
         num += static_cast<long long>(lines[j][i] - '0');
      }

      if (num > 0)
      {
         if (operation == '+')
         {
            subtotal += num;
         }
         else if (operation == '*')
         {
            subtotal *= num;
         }
      }
   }

   total += subtotal;

   return total;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 6 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 06 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 06 - Part 2:\n"
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
