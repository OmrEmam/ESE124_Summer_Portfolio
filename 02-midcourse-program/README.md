# CSV Grade Book

## Overview

Reads a CSV file of student grades, one student per line, and prints
each student's average. It's built to keep going even when a line in
the file is malformed, instead of crashing or silently skipping it.

## Key Features

- Reads `grades.csv` line by line with `fgets()`
- Parses each line with `sscanf()`, checking that all four fields
  (name, score1, score2, score3) actually parsed before trusting them
- Prints a clear error and moves on instead of stopping on a bad line
- Checks the `fopen()` result before touching the file pointer

## Compile and Run

```bash
cd 02-midcourse-program
make
./csv_gradebook
```

Needs a `grades.csv` in the same directory, formatted as
`name,score1,score2,score3` per line, e.g.:

```
Alice,88,92,79
Bob,73,65,81
```

## Example

```
$ ./csv_gradebook
Alice average: 86.3
Bob average: 73.0
```

With a malformed line added (`Tom,80`, missing a score):

```
Alice average: 86.3
Bob average: 73.0
Invalid line
```

## Design and Testing

The key design choice is checking `sscanf()`'s return value instead of
just trusting it parsed. `sscanf(line, " %99[^,],%d,%d,%d", ...)`
returns the number of fields it actually matched, so checking for `== 4`
is what lets a malformed line like `Tom,80` get caught and reported
instead of leaving `score2` and `score3` full of garbage and printing a
wrong average anyway.

Test cases, see `../TESTING.md`:

| Input | Expected |
|---|---|
| `Alice,88,92,79` | `Alice average: 86.3` |
| `Bob,73,65,81` | `Bob average: 73.0` |
| `Tom,80` (malformed) | `Invalid line` |

All three ran and matched.

**Bug fixed:** the original version printed each result as
`Name: Alice; Average: 86.3` instead of the required `Alice average:
86.3`. It's a one-line difference in the `printf()` format string, but
it's the kind of thing that's easy to miss since the output still
*looks* right at a glance, it's just not in the exact format the
assignment (and an autograder) actually checks for. Caught it by
comparing my program's output side by side with the assignment's sample
test cases instead of just eyeballing whether it "looked done."

## Acknowledgments

- Gemini and Claude, used for debugging help and explaining concepts
  while working through this
- ESE 124 starter code and problem statement, which came from the course
- ESE 124 lecture and lab material, for the file I/O and `sscanf()`
  parsing concepts this program is built on
