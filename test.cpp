#include "test.h"
#include "DynamicArray.h"
#include "DynamicArraySmart.h"
#include "LinkedList.h"
#include "LinkedListSmart.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <functional>
#include <iomanip>
#include "Sequence.h"


template<typename SequenceType>
void testSequence() {
    SequenceType seq;
    seq.Append(1);
    seq.Append(2);
    seq.Prepend(0);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 0);
    assert(seq.GetLast() == 2);
    assert(seq.Get(1) == 1);

    seq.InsertAt(5, 1);
    assert(seq.Get(1) == 5);
    assert(seq.GetLength() == 4);

    Sequence<int>* subseq = seq.GetSubsequence(1, 2);
    assert(subseq->GetLength() == 2);
    assert(subseq->Get(0) == 5);
    assert(subseq->Get(1) == 1);
    delete subseq;

    SequenceType seq2;
    seq2.Append(10);
    Sequence<int>* concatSeq = seq.Concat(&seq2);
    assert(concatSeq->GetLength() == 5);
    assert(concatSeq->Get(4) == 10);
    delete concatSeq;
}

void runFunctionalTests() {
    std::cout << "Running functional tests...\n";

    std::cout << "Testing DynamicArray with standard smart pointers...\n";
    testSequence<DynamicArray<int>>();

    std::cout << "Testing DynamicArraySmart with custom smart pointers...\n";
    testSequence<DynamicArraySmart<int>>();

    std::cout << "Testing LinkedList with standard smart pointers...\n";
    testSequence<LinkedList<int>>();

    std::cout << "Testing LinkedListSmart with custom smart pointers...\n";
    testSequence<LinkedListSmart<int>>();

    std::cout << "All functional tests have been passed successfully.\n";
}

double measureExecutionTime(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

void printPerformanceResults(
        const std::vector<int>& elementCounts,
        const std::vector<double>& customTimes,
        const std::vector<double>& standardTimes
) {
    std::cout << "\nPerformance Test Results:\n";
    std::cout << std::left << std::setw(15) << "Element Count" << std::setw(15) << "Standard Time"
              << std::setw(15) << "Custom Time" << std::setw(15) << "Difference (%)\n";

    for (size_t i = 0; i < elementCounts.size(); i++) {
        double difference = 100.0 * (customTimes[i] - standardTimes[i]) / standardTimes[i];
        std::cout << std::left << std::setw(15) << elementCounts[i]
                  << std::setw(15) << std::setprecision(2) << std::fixed << standardTimes[i]
                  << std::setw(15) << std::setprecision(2) << customTimes[i]
                  << std::setw(15) << std::setprecision(2) << difference << "%\n";
    }
}

void runPerformanceTests(
        std::vector<int>& elementCounts,
        std::vector<double>& customTimes,
        std::vector<double>& standardTimes
) {
    std::cout << "Running performance tests...\n";

    for (int n = 10; n <= 1000000; n *= 10) {
        elementCounts.push_back(n);
        std::cout << "Testing with the number of elements: " << n << "\n";

        double standardTime = measureExecutionTime([&]() {
            DynamicArray<int> array;
            for (int i = 0; i < n; ++i) {
                array.Append(i);
            }
        });
        standardTimes.push_back(standardTime);

        double customTime = measureExecutionTime([&]() {
            DynamicArraySmart<int> array;
            for (int i = 0; i < n; ++i) {
                array.Append(i);
            }
        });
        customTimes.push_back(customTime);
    }

    std::cout << "Performance tests completed.\n";
    printPerformanceResults(elementCounts, customTimes, standardTimes);
}
