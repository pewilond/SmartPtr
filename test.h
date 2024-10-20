#ifndef TEST_H
#define TEST_H

#include <vector>

void runFunctionalTests();

void runPerformanceTests(
        std::vector<int>& elementCounts,
        std::vector<double>& customTimes,
        std::vector<double>& standardTimes
);

#endif // TEST_H
