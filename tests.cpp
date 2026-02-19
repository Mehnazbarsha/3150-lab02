#include <iostream>
#include <cmath>
#include <cstring>
#include "BalancedParens.h"

using namespace std;

int passCount = 0;
int failCount = 0;

#define ASSERT_TRUE(cond, name) \
    do { \
        if (cond) { cout << "[PASS] " << name << endl; passCount++; } \
        else { cout << "[FAIL] " << name << endl; failCount++; } \
    } while(0)

int alwaysZero(int) { return 0; }

void test_fillArray() {
    int arr[6];
    fillArray(arr, 3);
    ASSERT_TRUE(arr[0] == 1 && arr[1] == 1 && arr[2] == 1, "fillArray: first n are 1");
    ASSERT_TRUE(arr[3] == -1 && arr[4] == -1 && arr[5] == -1, "fillArray: last n are -1");
}

void test_hasNonNegativePrefixSums_balanced() {
    int arr[] = {1, 1, -1, -1};
    ASSERT_TRUE(hasNonNegativePrefixSums(arr, 4), "prefix sums: balanced (1 1 -1 -1)");
}

void test_hasNonNegativePrefixSums_unbalanced() {
    int arr[] = {-1, 1, 1, -1};
    ASSERT_TRUE(!hasNonNegativePrefixSums(arr, 4), "prefix sums: unbalanced (-1 1 1 -1)");
}

void test_hasNonNegativePrefixSums_alternating() {
    int arr[] = {1, -1, 1, -1};
    ASSERT_TRUE(hasNonNegativePrefixSums(arr, 4), "prefix sums: alternating (1 -1 1 -1)");
}

void test_hasNonNegativePrefixSums_notes_example() {
    int arr[] = {-1, 1, 1, -1};
    ASSERT_TRUE(!hasNonNegativePrefixSums(arr, 4), "prefix sums: notes example -1 +1 +1 -1 unbalanced");
}

void test_fisherYates_preservesElements() {
    int arr[] = {1, 1, 1, -1, -1, -1};
    srand(99);
    fisherYates(arr, 6, pseudoRandom);
    int ones = 0, negs = 0;
    for (int i = 0; i < 6; i++) {
        if (arr[i] == 1) ones++;
        else if (arr[i] == -1) negs++;
    }
    ASSERT_TRUE(ones == 3 && negs == 3, "fisherYates: preserves element counts");
}

void test_fisherYates_deterministic_shuffle() {
    int arr[] = {1, 1, -1, -1};
    int orig[] = {1, 1, -1, -1};
    fisherYates(arr, 4, alwaysZero);
    ASSERT_TRUE(memcmp(arr, orig, 4 * sizeof(int)) != 0, "fisherYates: alwaysZero actually shuffles");
}

void test_runExperiment_convergence() {
    srand(42);
    int total, balanced;
    double ratio = runExperiment(3, 100000, 1e-4, total, balanced, pseudoRandom);
    ASSERT_TRUE(ratio > 0.0 && ratio <= 0.3, "experiment n=3: ratio converges in plausible range");
    ASSERT_TRUE(total >= 1000, "experiment: ran at least 1000 trials");
}

void test_runExperiment_reproducible() {
    srand(42);
    int t1, b1;
    double r1 = runExperiment(3, 10000, 1e-3, t1, b1, pseudoRandom);
    srand(42);
    int t2, b2;
    double r2 = runExperiment(3, 10000, 1e-3, t2, b2, pseudoRandom);
    ASSERT_TRUE(r1 == r2 && t1 == t2 && b1 == b2, "experiment: same seed produces same result");
}

void test_runExperiment_ratio_decreases_with_n() {
    srand(42);
    int t2, b2, t4, b4;
    double r2 = runExperiment(2, 20000, 1e-3, t2, b2, pseudoRandom);
    srand(42);
    double r4 = runExperiment(4, 20000, 1e-3, t4, b4, pseudoRandom);
    ASSERT_TRUE(r2 >= r4, "experiment: ratio decreases as n grows");
}

int main() {
    cout << "=== Running Unit Tests ===" << endl;

    test_fillArray();
    test_hasNonNegativePrefixSums_balanced();
    test_hasNonNegativePrefixSums_unbalanced();
    test_hasNonNegativePrefixSums_alternating();
    test_hasNonNegativePrefixSums_notes_example();
    test_fisherYates_preservesElements();
    test_fisherYates_deterministic_shuffle();
    test_runExperiment_convergence();
    test_runExperiment_reproducible();
    test_runExperiment_ratio_decreases_with_n();

    cout << "\n=== Results: " << passCount << " passed, " << failCount << " failed ===" << endl;
    return (failCount > 0) ? 1 : 0;
}