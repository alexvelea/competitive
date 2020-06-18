#include <iostream>
#include <map>
#include <vector>

template <typename T, typename T2>
std::ostream& operator<<(std::ostream& out, const std::map<T, T2>& rhs) {
    out << "[";
    for (auto& itr : rhs) {
        out << "{" << itr.first << ", " << itr.second << "}";
        if (itr != *rhs.rbegin()) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& rhs) {
    out << "[";
    for (int i = 0; i < (int)rhs.size(); i += 1) {
        out << rhs[i] << (i + 1 == (int)rhs.size() ? "" : ",\t");
    }
    out << "]";
    return out;
}

template <typename T>
void DebugPrint(const char*& allNames, T value) {
    std::string currentName = "";
    while (*allNames != '\0' and *allNames != ',') {
        currentName += *allNames;
        allNames++;
    }

    while (*allNames != '\0' and (*allNames == ',' or *allNames == ' ')) {
        allNames++;
    }

    std::cerr << currentName << " = " << value << '\t';
}

template <typename T>
void DebugSplitPrintHelper(const char*& allNames, T value) {
    DebugPrint(allNames, value);
}

template <typename T, typename... Args>
void DebugSplitPrintHelper(const char*& allNames, T value, Args... args) {
    DebugPrint(allNames, value);
    DebugSplitPrintHelper(allNames, args...);
}

template <typename... Args>
void DebugSplitPrint(const char* allNames, Args... args) {
    DebugSplitPrintHelper(allNames, args...);
    std::cerr << '\n';
}
