# Guessing game

## Rules
From an alphabet of `n` (n > 0) symbols a word `w` of lenght `L` (0 < L <= n) is selected, using every symbol max one time.

A guess consist of inputting a word `q` (same alphabet and length as w, using every symbol max one time). \
The results are the number of correct symbols but in the wrong position `s` and the number of correct symbols in the correct position `p`.

Continue guessing until: p == L <=> w == q (correct guess).

## Score
The score `g` is the number of guesses needed to match the hidden word.

## Question
Given n and L determine the optimal average score using only deterministic strategies.

## Known results
In file [naive_results.txt](naive_results.txt) the are the known results. \
n by row, L by column, starting with 0.
