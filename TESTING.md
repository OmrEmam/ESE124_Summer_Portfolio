# Testing

Manual test cases for the three artifacts in this portfolio. Each one
was run by hand and its actual output compared against the expected
result.

## 01-early-program — Magic Counter

**Test 1: repeat in the middle of mixed values**
Input: `1, -2, 0, 5, 5`
Expected: stops at the second 5; Positive: 3, Negative: 1, Zero: 1
Actual: `Positive: 3 / Negative: 1 / Zero: 1` — match

**Test 2: repeat is the very first pair**
Input: `0, 0`
Expected: stops immediately; Zero count is 2
Actual: `Positive: 0 / Negative: 0 / Zero: 2` — match

**Test 3: repeat among negative values**
Input: `-1, -2, -2`
Expected: stops at the second -2; Negative count is 3
Actual: `Positive: 0 / Negative: 3 / Zero: 0` — match

## 02-midcourse-program — CSV Grade Book

**Test 4: full sample file, clean and malformed lines mixed**
Input (`grades.csv`): `Alice,88,92,79` / `Bob,73,65,81` / `Tom,80`
Expected: `Alice average: 86.3`, `Bob average: 73.0`, then `Invalid line`
Actual: `Alice average: 86.3 / Bob average: 73.0 / Invalid line` — match

**Test 5: only clean lines**
Input: `Alice,88,92,79` / `Bob,73,65,81`
Expected: `Alice average: 86.3`, `Bob average: 73.0`
Actual: `Alice average: 86.3 / Bob average: 73.0` — match

**Test 6: only a malformed line**
Input: `Tom,80`
Expected: `Invalid line`
Actual: `Invalid line` — match

## 03-brobank

**Test 7: deposit, transfer, and withdrawal processed in order**
Setup: balances start at $100 / $50 / $0. Submit deposit $25 to
account 0, transfer $40 from 0 to 1, withdraw $10 from account 1.
Expected after processing: $85.00 / $80.00 / $0.00
Actual: `$85.00 / $80.00 / $0.00` — match

**Test 8: undo reverses the most recent transaction, not the first**
Setup: continues from Test 7, then call `brobankUndo`.
Expected: the withdrawal is reversed (account 1 goes back up by $10),
not the deposit or transfer.
Actual: `$85.00 / $90.00 / $0.00` — account 1 went from $80 to $90,
confirming the withdrawal (last processed) was the one undone — match

**Test 9: BFS distance after a transfer creates a graph edge**
Setup: continues from Test 7 — the transfer from account 0 to 1
already succeeded, so `graph[0][1] == 1`.
Expected: `brobankBFS(&bank, 0, 1)` returns 1 (one edge away)
Actual: `BFS distance 0 -> 1: 1 edge(s)` — match

**Test 10: DFS reachability for an account with no path**
Setup: same graph as above; account 2 never received a transfer from
account 0.
Expected: `brobankDFS(&bank, 0, 2)` returns false — no path exists
Actual: `DFS can reach 0 -> 2? no` — match
