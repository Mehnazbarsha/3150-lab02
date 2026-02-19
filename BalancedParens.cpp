#include "BalancedParens.h"
#include <cstdlib>

int32_t pseudoRandom(int limit) {
    return rand() % limit;
}

void fisherYates(int *array, int totalElements, int (*randomFcn)(int limit)) {
    for (int i = totalElements - 1; i > 0; i--) {
        int randomIndex = randomFcn(i);
        int temp = array[i];
        array[i] = array[randomIndex];
        array[randomIndex] = temp;
    }
}

void fillArray(int *array, int n) {
    for (int i = 0; i < 2 * n; i++) {
        array[i] = (i < n) ? 1 : -1;
    }
}

bool hasNonNegativePrefixSums(const int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
        if (sum < 0) return false;
    }
    return true;
}

bool runOneTrial(int n, int (*randomFcn)(int limit)) {
    int array[2 * n];
    fillArray(array, n);
    fisherYates(array, 2 * n, randomFcn);
    return hasNonNegativePrefixSums(array, 2 * n);
}

double runExperiment(int n, int maxTrials, double epsilon, int &totalTrials, int &balancedCount, int (*randomFcn)(int limit)) {
    totalTrials = 0;
    balancedCount = 0;
    double proportion = 0.0;
    double lastProportion = -1.0;

    for (int t = 0; t < maxTrials; t++) {
        if (runOneTrial(n, randomFcn)) {
            balancedCount++;
        }
        totalTrials++;

        proportion = static_cast<double>(balancedCount) / totalTrials;

        if (totalTrials >= 1000 && totalTrials % 500 == 0) {
            if (lastProportion >= 0.0 &&
                (proportion - lastProportion) * (proportion - lastProportion) < epsilon * epsilon) {
                break;
            }
            lastProportion = proportion;
        }
    }

    return proportion;
}