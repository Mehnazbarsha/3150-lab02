# Lab 2: Random Parentheses

Generates random +1/-1 sequences and measures what proportion are well-balanced (all prefix sums >= 0).

## Files

- `BalancedParens.h` — declarations
- `BalancedParens.cpp` — core logic
- `BalancedParensMain.cpp` — main program
- `tests.cpp` — unit tests

## Build & Run

```bash
chmod +x build.sh && ./build.sh
```

This compiles all files and automatically runs unit tests. If all tests pass, run the main program:

```bash
./main
```

Enter an integer `n` when prompted. The program will shuffle a sequence of 2n values and run thousands of trials, printing the observed ratio of well-balanced sequences and the Catalan estimate 1/(n+1).

## Algorithm

1. Fill array: first n = +1, last n = -1
2. Fisher-Yates shuffle using `std::rand`
3. Discard if any prefix sum is negative
4. Repeat until ratio converges