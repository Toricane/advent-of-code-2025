// Day 8
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>

using advent::read_lines;
using std::abs;
using std::cout;
using std::map;
using std::ostream;
using std::sort;
using std::sqrt, std::pow;
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

struct Box
{
   long long x;
   long long y;
   long long z;

   bool operator==(const Box &box) const
   {
      return x == box.x && y == box.y && z == box.z;
   }

   bool operator!=(const Box &box) const
   {
      return x != box.x || y != box.y || z != box.z;
   }
};

struct String
{
   unsigned iBox1;
   unsigned iBox2;
   long long distance;

   bool operator<(const String &box) const
   {
      return distance < box.distance;
   }
};

long long distance(const Box &a, const Box &b)
{
   long long x = abs(a.x - b.x);
   long long y = abs(a.y - b.y);
   long long z = abs(a.z - b.z);
   return x * x + y * y + z * z;
}

// compute the answer for Day 8 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<Box> boxes;
   boxes.reserve(lines.size());

   for (string line : lines)
   {
      if (line.empty())
      {
         continue;
      }

      Box box;
      stringstream ss(line);
      char comma;

      ss >> box.x >> comma >> box.y >> comma >> box.z;
      boxes.push_back(box);
   }

   vector<String> strings;

   for (unsigned i = 0; i < boxes.size(); i++)
   {
      for (unsigned j = i + 1; j < boxes.size(); j++)
      {
         strings.push_back(String{i, j, distance(boxes[i], boxes[j])});
      }
   }

   sort(strings.begin(), strings.end());

   vector<unsigned> ids;
   ids.resize(boxes.size());

   for (unsigned i = 0; i < boxes.size(); i++)
   {
      ids[i] = i;
   }

   unsigned limit = strings.size();
   if (limit >= 1000)
   {
      limit = 1000;
   }
   else
   {
      limit = 10;
   }

   for (unsigned i = 0; i < limit; i++)
   {
      String s = strings[i];

      unsigned id1 = ids[s.iBox1];
      unsigned id2 = ids[s.iBox2];

      if (id1 != id2)
      {
         for (unsigned j = 0; j < ids.size(); j++)
         {
            if (ids[j] == id2)
            {
               ids[j] = id1;
            }
         }
      }
   }

   map<int, int> circuits;

   for (unsigned i = 0; i < ids.size(); i++)
   {
      circuits[ids[i]]++;
   }

   vector<long long> sizes;

   for (auto const &[id, size] : circuits)
   {
      sizes.push_back(size);
   }

   sort(sizes.rbegin(), sizes.rend());

   if (sizes.size() >= 3)
   {
      return sizes[0] * sizes[1] * sizes[2];
   }

   return 0;
}

// compute the answer for Day 8 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   vector<Box> boxes;
   boxes.reserve(lines.size());

   for (string line : lines)
   {
      if (line.empty())
      {
         continue;
      }

      Box box;
      stringstream ss(line);
      char comma;

      ss >> box.x >> comma >> box.y >> comma >> box.z;
      boxes.push_back(box);
   }

   vector<String> strings;

   for (unsigned i = 0; i < boxes.size(); i++)
   {
      for (unsigned j = i + 1; j < boxes.size(); j++)
      {
         strings.push_back(String{i, j, distance(boxes[i], boxes[j])});
      }
   }

   sort(strings.begin(), strings.end());

   vector<unsigned> ids;
   ids.resize(boxes.size());

   for (unsigned i = 0; i < boxes.size(); i++)
   {
      ids[i] = i;
   }

   unsigned limit = strings.size();

   // part 2 code
   int remainingCircuits = boxes.size();

   for (unsigned i = 0; i < limit; i++)
   {
      String s = strings[i];

      unsigned id1 = ids[s.iBox1];
      unsigned id2 = ids[s.iBox2];

      if (id1 != id2)
      {
         for (unsigned j = 0; j < ids.size(); j++)
         {
            if (ids[j] == id2)
            {
               ids[j] = id1;
            }
         }

         remainingCircuits--;

         if (remainingCircuits == 1)
         {
            return boxes[s.iBox1].x * boxes[s.iBox2].x;
         }
      }
   }
   // end part 2 code

   return 0;
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 8 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 08 - Part 1: " << part1(lines) << '\n';
   out << "Day 08 - Part 2: " << part2(lines) << '\n';
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
