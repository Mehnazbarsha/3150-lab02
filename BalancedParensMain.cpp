#include <iostream>
#include <cstdlib>
#include "BalancedParens.h"

using namespace std;

int main() {
    srand(42);

    int n = 0;
    cout << "Enter n (generates sequences of length 2n): ";
    cin >> n;

    if (n <= 0) {
        cerr << "n must be a positive integer." << endl;
        return 1;
    }

    int demo[2 * n];
    fillArray(demo, n);
    fisherYates(demo, 2 * n, pseudoRandom);
    cout << "Example shuffled array: ";
    for (int i = 0; i < 2 * n; i++) cout << demo[i] << " ";
    cout << endl;
    cout << "Balanced: " << (hasNonNegativePrefixSums(demo, 2 * n) ? "yes" : "no") << endl;

    int totalTrials = 0, balancedCount = 0;
    int maxTrials = 100000;
    double epsilon = 1e-4;

    double proportion = runExperiment(n, maxTrials, epsilon, totalTrials, balancedCount, pseudoRandom);

    cout << endl;
    cout << "n: " << n << endl;
    cout << "Total trials: " << totalTrials << endl;
    cout << "Balanced count: " << balancedCount << endl;
    cout << "Observed ratio: " << proportion << endl;
    cout << "Catalan estimate 1/(n+1): " << 1.0 / (n + 1) << endl;

    return 0;
}