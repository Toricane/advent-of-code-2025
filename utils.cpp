#include "utils.h"

#include <cctype>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::isspace;
using std::istringstream;
using std::string;
using std::vector;

namespace advent
{
   vector<string> read_lines(const string &file_path)
   {
      vector<string> lines;
      ifstream input(file_path);
      if (!input)
      {
         return lines;
      }

      string line;
      while (std::getline(input, line))
      {
         if (!line.empty())
         {
            const char last = line[line.size() - 1];
            if (last == '\r')
            {
               line.pop_back();
            }
         }
         lines.push_back(line);
      }
      return lines;
   }
   vector<int> read_ints(const vector<string> &lines)
   {
      vector<int> numbers;
      const unsigned count = static_cast<unsigned>(lines.size());
      for (unsigned i = 0; i < count; ++i)
      {
         const vector<string>::size_type index = static_cast<vector<string>::size_type>(i);
         istringstream stream(lines[index]);
         int value = 0;
         while (stream >> value)
         {
            numbers.push_back(value);
         }
      }
      return numbers;
   }
   vector<int> read_ints_from_file(const string &file_path)
   {
      const vector<string> lines = read_lines(file_path);
      return read_ints(lines);
   }
   string trim(const string &text)
   {
      const unsigned length = static_cast<unsigned>(text.size());
      unsigned start = 0;
      while (start < length && isspace(static_cast<unsigned char>(text[start])))
      {
         ++start;
      }

      unsigned finish = length;
      while (finish > start && isspace(static_cast<unsigned char>(text[finish - 1])))
      {
         --finish;
      }

      return text.substr(start, finish - start);
   }
   vector<string> split(const string &text, char delimiter)
   {
      vector<string> tokens;
      string current;
      const unsigned length = static_cast<unsigned>(text.size());
      for (unsigned i = 0; i < length; ++i)
      {
         const string::size_type index = static_cast<string::size_type>(i);
         const char ch = text[index];
         if (ch == delimiter)
         {
            tokens.push_back(current);
            current.clear();
         }
         else
         {
            current.push_back(ch);
         }
      }
      tokens.push_back(current);
      return tokens;
   }

} // namespace advent
