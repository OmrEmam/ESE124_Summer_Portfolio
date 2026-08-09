# BroBank

## Overview

BroBank is a small in-memory banking engine I wrote in C. It takes in
transactions (deposits, withdrawals, transfers), processes them in order,
and lets you undo the last one if something goes wrong. It also tracks
which accounts have sent money to which other accounts, so you can check
if money could have flowed from one account to another using BFS and DFS.

## Key Features

- Deposits, withdrawals, and transfers, queued and processed in order
- Undo for the most recently processed transaction
- Directed account graph, built automatically as transfers happen
- BFS to find the shortest transfer path between two accounts
- DFS to check if one account can reach another at all

## Technical Highlights

The pending transactions sit in a circular queue (`p_front`, `p_rear`,
`p_count`), so they're handled first in, first out. Every transaction that
processes successfully gets pushed onto a stack (`undo`, `undo_top`), which
is what makes undo an O(1) operation instead of something that has to
search back through history.

The account graph is just an adjacency matrix (`graph[from][to]`), marked
whenever a transfer succeeds. `brobankBFS` walks it with a queue to find
the shortest path between two accounts, and `brobankDFS` walks it with a
stack to check reachability.

None of this works without `adt.c`/`adt.h`. `brobank.h` includes `adt.h`
directly for the `CAPACITY` constant and the `Stack`/`Queue` types the
queue, undo stack, and both searches are built on. It's not extra code
tagging along, it's a real dependency.

## Project Structure

- `brobank.h` / `brobank.c` — the `BroBank` struct and all the transaction,
  undo, and graph-search logic
- `adt.h` / `adt.c` — the generic Stack and circular Queue BroBank is built
  on top of
- `main.c` — a small demo that runs deposits, a transfer, a withdrawal, an
  undo, and both searches
- `Makefile` — builds the demo

## Compile and Run

```bash
make
./brobank
```

No input files needed. `main.c` sets up three demo accounts and a handful
of transactions on its own.

## Example

```
Starting balances:
  Account 0: $100.00
  Account 1: $50.00
  Account 2: $0.00

Processing 3 pending transactions...
  Account 0: $85.00
  Account 1: $80.00
  Account 2: $0.00

Undoing the last transaction (withdrawal)...
  Account 0: $85.00
  Account 1: $90.00
  Account 2: $0.00

Reachability after the transfer created account 0 -> 1:
  BFS distance 0 -> 1: 1 edge(s)
  DFS can reach 0 -> 2? no
```

## Design and Testing

I used fixed-size arrays for the pending queue and undo stack instead of
allocating memory dynamically. That keeps the whole `BroBank` struct's
size predictable and means no `malloc`/`free` bookkeeping to get wrong.
The tradeoff is a hard cap on how many pending transactions or undo steps
can pile up at once, which is fine for this project but wouldn't scale to
a real bank.

CHECK `/TESTING.md`:
But, One test I did: submit a $40
transfer from account 0 to account 1, process it, then check
`brobank.graph[0][1] == 1`. That's the line that makes `brobankBFS(&bank,
0, 1)` return `1` instead of `-1`, so it's a good check that the graph is
actually getting built, not just the balances.

**Bug fixed:** One bug that I ran into was not using `->` correctly. Since it dereferences stuff into pointers back to their parent it is important.

## Acknowledgments

- Gemini and Claude, used for debugging help and explaining concepts
  while I worked through this
- ESE 124 starter code, the base structure for `adt.h`, `brobank.h`, and
  the rest of the exercise came from the course
- ESE 124 lecture and lab material, for the ADT, queue/stack, and graph
  traversal concepts this project is built on
