# Guessing game

## Rules
From an alphabet of `n` symbols a word `w` of lenght `l` (0 < l < = n) is selected, using every symbol max one time.

A guess consist of inputting a word `q` (same alphabet and length as w, using every symbol max one time). \
The results are the number of correct symbols but in the wrong position `s` and the number of correct symbols in the correct position `p`.

Continue guessing until: p == l <=> w == q (correct guess).

## Score
The score `g` is the number of guesses needed to match the hidden word.

## Question
Given n and l determine the optimal average score using only deterministic strategies.
