#ifndef HASHCODE_HASHCODE_HPP
#define HASHCODE_HASHCODE_HPP
#include <string>
#include <fstream>
#include <cassert>

#include "Debug.hpp"
#include "Logger.hpp"
#include "Macros.hpp"
#include "Output.hpp"

int test_number;

std::string InputFile() {
    return "tests/test-" + std::to_string(test_number) + ".in";
}

std::string AnsFile() {
    return "answers/test-" + std::to_string(test_number) + ".ans";
}

std::string BestCostFile() {
    return "answers/test-" + std::to_string(test_number) + ".best_cost";
}

std::string LockFile() {
    return "locks/test-" + std::to_string(test_number) + ".lock";
}

std::ifstream GetInputStream() {
    std::ifstream in(InputFile().c_str());
    if (!in) {
        Die("Error while reading file %s\n", InputFile().c_str());
    }

    return in;
}

void InitHashCode(int argc, char** argv) {
    if (argc == 1) {
        Die("Run with ./exec 1 for test 1");
    }

    test_number = atoi(argv[1]);
}

#endif // HASHCODE_HASHCODE_HPP
