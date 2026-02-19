#ifndef BALANCED_PARENS_H
#define BALANCED_PARENS_H

#include <vector>
#include <cstdint>

int32_t pseudoRandom(int limit);

void fisherYates(int *array, int totalElements, int (*randomFcn)(int limit));

void fillArray(int *array, int n);

bool hasNonNegativePrefixSums(const int *array, int size);

bool runOneTrial(int n, int (*randomFcn)(int limit));

double runExperiment(int n, int maxTrials, double epsilon, int &totalTrials, int &balancedCount, int (*randomFcn)(int limit));

#endif