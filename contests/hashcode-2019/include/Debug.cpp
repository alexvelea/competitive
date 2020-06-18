#include "Debug.hpp"

#include <iostream>

void DebugPrint(const char*& allNames, const char* value) {
    std::string name = "";
    while (*allNames != '\0' and *allNames != ',') {
        name += *allNames;
        allNames++;
    }

    while (*allNames != '\0' and (*allNames == ',' or *allNames == ' ')) {
        allNames++;
    }

    if (name == "\"\\n\"") {
        std::cerr << "\n";
        return ;
    }

    std::string sValue = value;
    if (name.substr(1, sValue.size()) == sValue) {
        std::cerr << sValue << '\t';
    } else {
        std::cerr << name << " = " << sValue << '\t';
    }
}

