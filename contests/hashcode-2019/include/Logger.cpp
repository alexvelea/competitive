#include "Logger.hpp"

#include <execinfo.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <functional>
#include <string>
#include <vector>

#define NONRET __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define GENERATE_PRINTF_WARNINGS __attribute__((format(printf, 1, 2)))

int verboseLevel = 0;
int msgFd = 2;
int dieFd = 2;

std::function<void(std::string)> DieExitFunction;

static const int kDieBufferSize = 1 << 13;
static const int kDieStackSize = 50;

std::vector<std::string> GetCallStack() {
    void* voidStack[kDieStackSize];  // stack len

    size_t stackSize = backtrace(voidStack, sizeof(voidStack));
    char** stringStack = backtrace_symbols(voidStack, stackSize);

    std::vector<std::string> stack;
    for (size_t i = 0; i < stackSize; i += 1) {
        stack.push_back(stringStack[i]);
    }

    free(stringStack);
    return stack;
}

void xwrite(int fd, const char* head, int remaining) {
    while (1) {
        int len = write(fd, head, remaining);  // hope it doesn't crash somehow
        if (len == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                break;
            }
        } else {
            head += len;
            remaining -= len;
            if (remaining == 0) {
                break;
            }
        }
    }
}

std::string EscapeQuotes(const char* msg) {
    std::string result = "";
    while (*msg != '\0') {
        if (*msg == '\"') {
            result += "\\\"";
        } else if (*msg == '\'') {
            result += "\\\'";
        } else {
            result += *msg;
        }
        msg++;
    }
    return result;
}

void NONRET Die(const char* fieldName, const char* msg, bool isJsonObject) {
    std::string json = "{";

    json += "\"" + std::string(fieldName) + "\":";
    if (isJsonObject) {
        json += std::string(msg);
    } else {
        json += "\"" + EscapeQuotes(msg) + "\"";
    }

    json += ",\n";
    json += "\"callstack\":[\n";

    auto callStack = GetCallStack();
    for (auto& itr : callStack) {
        json += "    \"" + itr + "\",\n";
    }

    if (callStack.size()) {
        json.pop_back();  // remove last \n
        json.pop_back();  // remove last ,
        json += "\n";
    }

    json += "]}\n";

    // write errors to dieFd first
    xwrite(dieFd, json.c_str(), json.size());

    if (DieExitFunction) {
        DieExitFunction(json);
    }

    close(dieFd);
    exit(2);
}

/* Report an error of the sandbox itself */
void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    char buff[kDieBufferSize];
    int n = vsnprintf(buff, sizeof(buff) - 1, msg, args);
    buff[n] = '\0';

    Die("message", buff, false);
}

void DieLogToFile(const std::string& filePath) {
    int fd = open(filePath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fd == -1) {
        Die("Cant redirect Die log's to file: %s", filePath.c_str());
    }
    dieFd = fd;
}

void __attribute__((format(printf, 2, 3))) Msg(int verbosity, const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    if (verbosity <= verboseLevel) {
        vdprintf(msgFd, msg, args);
    }

    va_end(args);

    if (msg[strlen(msg) - 1] == '\n') {
        fsync(msgFd);
    }
}

void __attribute__((format(printf, 1, 2))) Msg(const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    if (1 <= verboseLevel) {
        vdprintf(msgFd, msg, args);
    }

    va_end(args);

    if (msg[strlen(msg) - 1] == '\n') {
        fsync(msgFd);
    }
}
