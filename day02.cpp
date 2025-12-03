// Day 2
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::string;
using std::stringstream;
using std::to_string;
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

// compute the answer for Day 2 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   string line = lines[0] + ',';
   string idis, idfs;
   long long idi, idf;
   long long sum = 0;
   bool first = true;
   stringstream ranges(line);
   char ch;
   string is;

   while (ranges >> ch)
   {
      if (ch != '-' && ch != ',')
      {
         if (first)
         {
            idis.push_back(ch);
         }
         else
         {
            idfs.push_back(ch);
         }
      }
      else if (ch == '-')
      {
         first = false;
      }
      else
      {
         idi = stoll(idis);
         idf = stoll(idfs);

         for (long long i = idi; i <= idf; i++)
         {
            is = to_string(i);

            if (is.size() % 2 == 1)
            {
               continue;
            }

            if (is.substr(0, is.size() / 2) == is.substr(is.size() / 2))
            {
               sum += i;
            }
         }

         first = true;
         idis = "";
         idfs = "";
      }
   }

   return sum;
}

// compute the answer for Day 2 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   string line = lines[0] + ',';
   string idis, idfs;
   long long idi, idf;
   long long sum = 0;
   bool first = true;
   stringstream ranges(line);
   char ch;
   string is;
   long long maxSub;
   string sub;

   while (ranges >> ch)
   {
      if (ch != '-' && ch != ',')
      {
         if (first)
         {
            idis.push_back(ch);
         }
         else
         {
            idfs.push_back(ch);
         }
      }
      else if (ch == '-')
      {
         first = false;
      }
      else
      {
         idi = stoll(idis);
         idf = stoll(idfs);

         for (long long i = idi; i <= idf; i++)
         {
            is = to_string(i);

            maxSub = is.size() / 2;

            if (maxSub < 1)
            {
               continue;
            }

            for (long long j = 1; j <= maxSub; j++)
            {
               if (is.size() % j != 0)
               {
                  continue;
               }

               bool match = true;

               for (long long k = 0; k < is.size(); k += j)
               {
                  if (is.substr(0, j) != is.substr(k, j))
                  {
                     match = false;
                     break;
                  }
               }

               if (match)
               {
                  sum += i;
                  break;
               }
            }
         }

         first = true;
         idis = "";
         idfs = "";
      }
   }

   return sum;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 2 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 02 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 02 - Part 2:\n"
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
