# Evidence of Algorithm's Correctness: PDA for Words NOT in {a^nb^n, n>=0}

<b>Created by:</b> Miriam Briskman

<b>Date:</b>: 04/13/2021

## Info

This repo contains a simple `C++` program testing a PDA for recognizing words not of the form `a^nb^n, n>= 0`.
The program accepts a natural number (`m >= 1`), and recursively creates strings over `{a,b}` of sizes less than or equal to `m`. In other words, it creates all the strings in the power set of `{a,b}`. Then, the program tests the algorithm on each of those strings to check if the word represented by the string is accepted or rejected.

## The Algorithm
Here is a pseudo-code ("informal description") of the PDA:
- Begin the PDA by pushing a `$` sign into the stack. 

- For each char in the input string:
  - If this is `a`:
    - If `b` was the most recently read char before this `a`:
      - Accept the word (since we got a substring of the form `ba`, which is not allowed in `a^nb^n`.)
    - Otherwise, push an `a` onto the stack. 
  - Otherwise, for each encountered b, pop an `a` from the stack. 
    - If a `$` symbol is popped from the stack:
      - Accept the word (the string begins with b's or there are more b's than a's.) 

- When there are no more symbols to read from the input string, pop a symbol from the stack.
- If this symbol is an `a`:
  - Accept the word (there are more a's than b's.)
  - If this is the `$` symbol, reject the word (there are as many a's as b's.)

## Get Started

1. Do git clone
2. In a terminal, compile as `g++ -o prog prog.c`.
3. Run as `prog.exe NUM` (Windows) or `./prog NUM` (Mac, Linux)
   Note that NUM is an integer, such as 1, 2, 3, etc.
4. You can add the option `-c` or `--comments`, such as in: `./prog -c NUM` or `./prog -- comments NUM`
   to see all the stack operations (what was pushed or popped before the program accepted/rejected the word.)

## Example
When we call `prog.exe 4` or `./prog 4`, the following is printed to the console/terminal:
```
The empty word is rejected! (it's of the form a^0b^0)
The word: a is accepted!
The word: aa is accepted!
The word: aaa is accepted!
The word: aaaa is accepted!
The word: aaab is accepted!
The word: aab is accepted!
The word: aaba is accepted!
The word: aabb is rejected!
The word: ab is rejected!
The word: aba is accepted!
The word: abaa is accepted!
The word: abab is accepted!
The word: abb is accepted!
The word: abba is accepted!
The word: abbb is accepted!
The word: b is accepted!
The word: ba is accepted!
The word: baa is accepted!
The word: baaa is accepted!
The word: baab is accepted!
The word: bab is accepted!
The word: baba is accepted!
The word: babb is accepted!
The word: bb is accepted!
The word: bba is accepted!
The word: bbaa is accepted!
The word: bbab is accepted!
The word: bbb is accepted!
The word: bbba is accepted!
The word: bbbb is accepted!
```

<hr>

Thanks for reading! :)
-- Miriam Briskman
