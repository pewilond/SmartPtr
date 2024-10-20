#include "interface.h"
#include "DynamicArraySmart.h"
#include "LinkedListSmart.h"
#include "test.h"
#include "displayCharts.h"
#include <iostream>
#include <random>
#include <limits>
#include <chrono>

int getValidatedInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "Invalid input. Please enter an integer value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

template<typename SequenceType>
void workWithSequence(const std::string& sequenceName) {
    SequenceType sequence;
    int choice;
    do {
        std::cout << "\n=== " << sequenceName << " Menu ===\n";
        std::cout << "1. Append an element\n";
        std::cout << "2. Prepend an element\n";
        std::cout << "3. Insert an element at index\n";
        std::cout << "4. Get an element by index\n";
        std::cout << "5. Display the sequence\n";
        std::cout << "6. Fill the sequence with random numbers\n";
        std::cout << "0. Return to main menu\n";
        choice = getValidatedInt("Select an option: ");

        switch (choice) {
            case 1: {
                int value = getValidatedInt("Enter the value: ");
                sequence.Append(value);
                break;
            }
            case 2: {
                int value = getValidatedInt("Enter the value: ");
                sequence.Prepend(value);
                break;
            }
            case 3: {
                int index = getValidatedInt("Enter the index: ");
                int value = getValidatedInt("Enter the value: ");
                try {
                    sequence.InsertAt(value, index);
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                int index = getValidatedInt("Enter the index: ");
                try {
                    int value = sequence.Get(index);
                    std::cout << "Element at index " << index << ": " << value << "\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                std::cout << sequenceName << ": ";
                for (int i = 0; i < sequence.GetLength(); ++i) {
                    std::cout << sequence.Get(i) << " ";
                }
                std::cout << "\n";
                break;
            }
            case 6: {
                int n = getValidatedInt("Enter the number of elements: ");
                int minVal = getValidatedInt("Enter the minimum value: ");
                int maxVal = getValidatedInt("Enter the maximum value: ");
                if (minVal > maxVal) {
                    std::swap(minVal, maxVal);
                }
                std::mt19937 gen(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
                std::uniform_int_distribution<> dis(minVal, maxVal);

                for (int i = 0; i < n; ++i) {
                    sequence.Append(dis(gen));
                }
                std::cout << sequenceName << " filled with random numbers.\n";
                break;
            }
            case 0:
                std::cout << "Returning to main menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
}

void run_interface() {
    int choice;
    do {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Work with DynamicArraySmart\n";
        std::cout << "2. Work with LinkedListSmart\n";
        std::cout << "3. Run tests\n";
        std::cout << "0. Exit\n";
        choice = getValidatedInt("Select an option: ");

        switch (choice) {
            case 1:
                workWithSequence<DynamicArraySmart<int>>("DynamicArraySmart");
                break;
            case 2:
                workWithSequence<LinkedListSmart<int>>("LinkedListSmart");
                break;
            case 3:
                runTestsAndDisplayResults();
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
}

void runTestsAndDisplayResults() {
    runFunctionalTests();

    std::vector<int> elementCounts;
    std::vector<double> customTimes;
    std::vector<double> standardTimes;

    runPerformanceTests(
            elementCounts,
            customTimes,
            standardTimes
    );
    displayCharts(elementCounts, customTimes, standardTimes);
}
