# Lab 02: Random Parentheses

Generates random +1/-1 sequences and measures what proportion are well-balanced (all prefix sums >= 0).

## Files

- `BalancedParens.h` 
- `BalancedParens.cpp` 
- `BalancedParensMain.cpp` 
- `tests.cpp` 

## Build & Run

```bash
g++ -std=c++17 -Wall -o tests tests.cpp BalancedParens.cpp && ./tests

g++ -std=c++17 -Wall -o main BalancedParensMain.cpp BalancedParens.cpp && ./main
```

## Algorithm

1. Fill array: first n = +1, last n = -1
2. Fisher-Yates shuffle using `std::rand`
3. Discard if any prefix sum is negative
4. Repeat until ratio converges