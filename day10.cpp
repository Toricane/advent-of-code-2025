// Day 10
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <sstream>

using advent::read_lines;
using std::cout;
using std::ostream;
using std::pair;
using std::queue;
using std::string;
using std::stringstream;
using std::unordered_set;
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

int solve_machine(long long target, const vector<int> &buttons)
{
   queue<pair<long long, int>> q;
   unordered_set<long long> visited;

   q.push({0, 0});
   visited.insert(0);

   while (!q.empty())
   {
      auto [current_state, dist] = q.front();
      q.pop();

      if (current_state == target)
      {
         return dist;
      }

      for (int btn_mask : buttons)
      {
         long long next_state = current_state ^ btn_mask;

         if (visited.find(next_state) == visited.end())
         {
            visited.insert(next_state);
            q.push({next_state, dist + 1});
         }
      }
   }

   return -1;
}

// compute the answer for Day 10 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   long long total_presses = 0;

   for (string line : lines)
   {
      if (line.empty())
      {
         continue;
      }

      string lights = line.substr(1, line.find(']') - 1);
      int target_state = 0;

      for (unsigned i = 0; i < lights.length(); i++)
      {
         if (lights[i] == '#')
         {
            target_state |= (1 << i);
         }
      }

      string buttons_section = line.substr(line.find(']') + 2, line.find('{') - line.find(']') - 3);

      vector<int> button_masks;
      size_t pos = 0;

      while ((pos = buttons_section.find('(', pos)) != string::npos)
      {
         size_t end = buttons_section.find(')', pos);
         string content = buttons_section.substr(pos + 1, end - pos - 1);

         int current_btn_mask = 0;
         size_t comma_pos = 0;
         size_t start = 0;

         while ((comma_pos = content.find(',', start)) != string::npos)
         {
            int light_index = stoi(content.substr(start, comma_pos - start));
            current_btn_mask |= (1 << light_index);
            start = comma_pos + 1;
         }

         int last_index = stoi(content.substr(start));
         current_btn_mask |= (1 << last_index);

         button_masks.push_back(current_btn_mask);
         pos = end + 1;
      }

      total_presses += solve_machine(target_state, button_masks);
   }

   return total_presses;
}

// compute the answer for Day 10 Part 2 based on the parsed input
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
//    writes both Advent of Code Day 10 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 10 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 10 - Part 2:\n"
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
