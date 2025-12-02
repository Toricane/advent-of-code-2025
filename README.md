# 🗓️ [Advent of Code 2025](https://adventofcode.com)

From Nov. 30 through Dec. 11 we will sharpen our C++ skills with the daily Advent of Code puzzles. Whether you are brand new to coding or you finished every puzzle last year, all you need is a problem-solving mindset and this repository.

## 🖥️ Why join?

-   Good practice for the C++ final exam.
-   Solve puzzles at your own pace and have fun along the way.
-   Stretch your technical muscles by discovering new patterns and algorithms.

## 🌟 How do I join?

1. Visit [adventofcode.com](https://adventofcode.com/) and sign in (GitHub works great, but any option is fine).
2. Join our private leaderboard with code `3297738-f38ef45e` at [adventofcode.com/2025/leaderboard/private](https://adventofcode.com/2025/leaderboard/private).
3. Head to the course Discord `<id:customize>` channel to grab the 🎄 Advent of Code role.
4. Prefer spectating? Bookmark the read-only leaderboard view: [https://adventofcode.com/2025/leaderboard/private/view/3297738?view_key=f9e70783](https://adventofcode.com/2025/leaderboard/private/view/3297738?view_key=f9e70783).

> 🗓️ New challenges drop nightly at 9:00 p.m. PT. Check `#advent-of-code` for reminders and feel free to hop into VC ("General") while solving.

Good luck and have fun — adapted (with thanks) from [BCYDC](https://bcydc.ca/).

---

## Repository quick start

1. Copy your personal puzzle input into `data.txt`.
2. Open the corresponding `dayNN.cpp` (e.g., `day01.cpp`).
3. Implement the `part1` and `part2` functions using any helpers you need.
4. Build with `make dayNN` and run the produced executable (`./dayNN` or `dayNN.exe`).
5. Submit your answer on the Advent of Code website and enjoy the ⭐.

### Directory layout

-   `day01.cpp` … `day12.cpp`
    -   Each file already wires up `parse_input`, `part1`, `part2`, a `solve` coordinator, and `main`.
    -   Duplicate the pattern for additional days after the 12th or create new files as needed.
-   `utils.h` / `utils.cpp`
    -   Shared helpers inside namespace `advent`; the header pulls in common types with `using std::string;` and `using std::vector;` so the signatures stay compact, and the documentation blocks spell out preconditions and postconditions.
-   `data.txt`
    -   Shared scratchpad for whichever puzzle you are solving; you can also pass a different filename to the helper functions.
-   `Makefile`
    -   Builds an executable per day and provides clean-up targets.

### Day file anatomy

Every day file follows the same structure so you know where to plug in logic:

-   `parse_input()` reads `data.txt` and returns a `vector<string>` with one line per entry.
-   `part1(const vector<string>&)` consumes the parsed lines and returns the Part 1 answer (`long long`).
-   `part2(const vector<string>&)` mirrors Part 1 for the second half of the puzzle.
-   `solve(ostream&)` orchestrates parsing, invokes both parts, and prints nicely formatted results.
-   `main()` simply calls `solve(cout)`; feel free to add command-line parsing if you need alternate inputs.

Keep the documentation blocks up to date as you refine each function—this mirrors the expectations for CPSC 1155 submissions.

### Utilities reference

All helpers live in the `advent` namespace (`#include "utils.h"`). The header already introduces the core STL types with `using` declarations to keep call sites tidy, and each function is documented with pre/postconditions; here is a quick summary:

-   `vector<string> read_lines(string file_path = "data.txt")`
    -   Loads every line from the chosen file, normalizes Windows line endings, and returns an ordered vector.
-   `vector<int> read_ints(const vector<string>& lines)`
    -   Extracts every whitespace-separated integer from the provided lines (non-numeric tokens are ignored).
-   `vector<int> read_ints_from_file(string file_path = "data.txt")`
    -   Convenience version that combines `read_lines` and `read_ints`.
-   `string trim(const string& text)`
    -   Removes leading and trailing ASCII whitespace.
-   `vector<string> split(const string& text, char delimiter)`
    -   Splits on the delimiter, returning empty tokens when appropriate.

Extend these helpers as you discover common routines (grid parsing, coordinate math, etc.); just add declarations to `utils.h` and implementations to `utils.cpp`.

## Build and housekeeping

Compile a specific day with either command:

```text
make dayNN        # example: make day12
make DAY=NN day   # example: make DAY=03 day
```

The target produces `dayNN` (plus `dayNN.exe` on Windows) by compiling `dayNN.cpp` alongside `utils.cpp` with C++20 flags (`-Wall -Wextra -pedantic -g`).

Cleanup options:

```text
make clean   # remove Windows artefacts (.exe, .obj, .o)
make remove  # remove POSIX artefacts if you build under WSL or Linux
```

## Suggested workflow

1. Read the puzzle story and examples on Advent of Code.
2. Sketch the algorithm and data structures you will need.
3. Update `parse_input` if the input format requires preprocessing.
4. Implement `part1`, compile, and test with the sample cases (you can hard-code them in a temporary file or use assertions).
5. Once Part 1 is confirmed, extend or refactor for Part 2.
6. Submit answers, then commit your solution so you can revisit it later.

Need inspiration? Browse [the previous year’s puzzles](https://adventofcode.com/2024) and try solving a warm-up day before December begins.

Happy coding, and enjoy this year’s Advent of Code challenge!
