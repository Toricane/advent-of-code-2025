// Day 11
// Name: Prajwal Prashanth

#include "utils.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using advent::read_lines;
using std::cout;
using std::map;
using std::ostream;
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

struct Node
{
   string device;
   vector<string> outputs;
   vector<string> back;
};

Node get_node(const vector<Node> &nodes, string device)
{
   for (Node node : nodes)
   {
      if (node.device == device)
      {
         return node;
      }
   }

   return Node{"out", vector<string>{}, vector<string>{}};
}

// compute the answer for Day 11 Part 1 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 1 result as a 64-bit integer
long long part1(const vector<string> &lines)
{
   vector<Node> nodes;
   nodes.reserve(lines.size());

   for (string line : lines)
   {
      if (line.empty())
      {
         continue;
      }

      Node node;
      node.device = line.substr(0, 3);

      string outputs = line.substr(5);
      stringstream ss(outputs);
      string output;

      while (ss >> output)
      {
         node.outputs.push_back(output);
      }

      nodes.push_back(node);
   }

   vector<Node> check;
   Node you = get_node(nodes, "you");
   check.push_back(you);

   Node node;
   long long numPaths = 0;

   while (!check.empty())
   {
      node = check.back();
      check.pop_back();

      if (node.device == "out")
      {
         numPaths++;
      }
      else
      {
         for (string output : node.outputs)
         {
            check.push_back(get_node(nodes, output));
         }
      }
   }

   return numPaths;
}

long long count_paths(string current, string target, map<string, long long> &memo, map<string, vector<string>> &nodesMap)
{
   if (current == target)
   {
      return 1;
   }
   if (memo.count(current))
   {
      return memo[current];
   }

   long long total = 0;

   for (string output : nodesMap[current])
   {
      total += count_paths(output, target, memo, nodesMap);
   }

   memo[current] = total;
   return total;
}

// compute the answer for Day 11 Part 2 based on the parsed input
// preconditions:
//    lines contains the puzzle input returned from parse_input()
// postconditions:
//    returns the computed Part 2 result as a 64-bit integer
long long part2(const vector<string> &lines)
{
   map<string, vector<string>> nodesMap;

   for (string line : lines)
   {
      if (line.empty())
      {
         continue;
      }

      Node node;
      node.device = line.substr(0, 3);

      string outputs = line.substr(5);
      stringstream ss(outputs);
      string output;

      while (ss >> output)
      {
         node.outputs.push_back(output);
      }

      nodesMap[node.device] = node.outputs;
   }

   map<string, long long> memo;

   long long dac_to_fft = count_paths("dac", "fft", memo, nodesMap);

   if (dac_to_fft > 0) {
      memo.clear();
      long long svr_to_dac = count_paths("svr", "dac", memo, nodesMap);

      memo.clear();
      long long ftt_to_out = count_paths("fft", "out", memo, nodesMap);

      return svr_to_dac * dac_to_fft * ftt_to_out;
   } else {
      memo.clear();
      long long svr_to_fft = count_paths("svr", "fft", memo, nodesMap);

      memo.clear();
      long long fft_to_dac = count_paths("fft", "dac", memo, nodesMap);

      memo.clear();
      long long dac_to_out = count_paths("dac", "out", memo, nodesMap);

      return svr_to_fft * fft_to_dac * dac_to_out;
   }
}

// orchestrate input parsing and rendering of both part results
// preconditions:
//    out is a valid output stream ready for writing
// postconditions:
//    writes both Advent of Code Day 11 answers to the stream
void solve(ostream &out)
{
   const vector<string> lines = parse_input();
   out << "Day 11 - Part 1:\n"
       << part1(lines) << '\n';
   out << "Day 11 - Part 2:\n"
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
