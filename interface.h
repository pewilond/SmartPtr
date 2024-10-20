#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

int getValidatedInt(const std::string& prompt);

template<typename SequenceType>
void workWithSequence(const std::string& sequenceName);

void run_interface();

void runTestsAndDisplayResults();

#endif // INTERFACE_H
