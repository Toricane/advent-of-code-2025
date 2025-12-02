#pragma once

#include <string>
#include <vector>

namespace advent
{

   using std::string;
   using std::vector;

   // read every line from file_path, preserving order and handling CRLF endings
   // preconditions:
   //    file_path identifies a readable text file (defaults to data.txt)
   // postconditions:
   //    returns a vector of strings containing all lines from the file
   vector<string> read_lines(const string &file_path = "data.txt");

   // parse all whitespace-separated integers from the supplied lines
   // preconditions:
   //    lines contains any number of strings with optional integer tokens
   // postconditions:
   //    returns a vector with every parsed integer in encounter order
   vector<int> read_ints(const vector<string> &lines);

   // convenience wrapper that reads a file then converts every integer token
   // preconditions:
   //    file_path identifies a readable text file containing integer tokens
   // postconditions:
   //    returns a vector containing all integers parsed from the file
   vector<int> read_ints_from_file(const string &file_path = "data.txt");

   // remove leading and trailing ASCII whitespace characters from text
   // preconditions:
   //    text may be any string
   // postconditions:
   //    returns a trimmed copy with surrounding whitespace removed
   string trim(const string &text);

   // split text on the provided delimiter, returning all tokens (empty allowed)
   // preconditions:
   //    text may contain zero or more delimiter characters
   // postconditions:
   //    returns a vector of substrings separated by delimiter
   vector<string> split(const string &text, char delimiter);

} // namespace advent
