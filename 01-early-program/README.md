# Magic Counter

## Overview

This program reads integers one at a time and stops as soon as the same
value shows up twice in a row. Along the way it keeps a running count of
how many positives, negatives, and zeros it saw.

## Key Features

- Reads integers one at a time, no fixed count needed up front
- Stops automatically the moment a value repeats consecutively
- Counts positives, negatives, and zeros as it goes, not after the fact

## Compile and Run

```bash
cd 01-early-program
make
./magic_counter
```

It'll keep prompting for one integer at a time until two matching values
show up back to back.

## Example

```
Enter an integer: 1
Enter an integer: -2
Enter an integer: 0
Enter an integer: 5
Enter an integer: 5
Positive: 3
Negative: 1
Zero: 1
```

## Design and Testing

The part of this I actually learned something from is the `has_previous`
flag. My first instinct was to just compare `current == previous` every
loop, but on the very first read there's no previous value yet, so that
comparison is comparing against garbage. `has_previous` starts at 0 and
only flips to 1 after the first value is read, so the repeat-check is
skipped entirely until there's actually something to compare against.
It's a small fix, but it's the kind of bug that's easy to miss until you
run it and the very first input you type matches whatever garbage was
sitting in `previous`.

Test cases, see `../TESTING.md`:

| Input | Expected |
|---|---|
| 1, -2, 0, 5, 5 | Stops at the second 5; Positive: 3, Negative: 1, Zero: 1 |
| 0, 0 | Stops immediately; Zero: 2 |
| -1, -2, -2 | Stops at the second -2; Negative: 3 |

All three ran and matched exactly.

## Acknowledgments

- Gemini and Claude, used for debugging help and explaining concepts
  while working through this
- ESE 124 starter code and problem statement, which came from the course
- ESE 124 lecture and lab material, for the loop and flag-variable
  concepts this program is built on
