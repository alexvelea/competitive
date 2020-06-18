#ifndef HASHCODE_LOGGER_HPP
#define HASHCODE_LOGGER_HPP

#include <functional>
#include <string>
#include <vector>

#include "Macros.hpp"

extern int verboseLevel;

void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...);

extern std::function<void(std::string)> DieExitFunction;

std::vector<std::string> GetCallStack();

void xwrite(int fd, const char* head, int remaining);

std::string EscapeQuotes(const char* msg);

void NONRET Die(const char* fieldName, const char* msg, bool isJsonObject);

/* Report an error of the sandbox itself */
void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...);

void DieLogToFile(const std::string& filePath);

void __attribute__((format(printf, 2, 3))) Msg(int verbosity, const char* msg, ...);

void __attribute__((format(printf, 1, 2))) Msg(const char* msg, ...);

#ifndef hashcodeuselib
#include "Logger.cpp"
#endif

#endif // HASHCODE_LOGGER_HPP
