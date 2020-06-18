#include "Output.hpp"

#include <fcntl.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "Debug.hpp"

extern int test_number;

std::string AnsFile();
std::string BestCostFile();
std::string LockFile();

int num_dump_calls = 0;

std::ofstream GetAnsStream() {
    std::ofstream fout(AnsFile().c_str());
    return fout;
}

bool to_be_killed = false;
bool dumping = false;

static void EnsureNiceRelease(int) {
    if (not dumping) {
        exit(0);
    }
    to_be_killed = true;
}


bool CheckUpgrade(BaseOutput& output) {
    double mx_cost;
    std::ifstream fin(BestCostFile().c_str());
    fin >> mx_cost;
    fin.close();

    double my_cost = output.Cost();

    if (mx_cost < my_cost) {
        std::ofstream fout(BestCostFile().c_str());
        std::cerr << "Found a better solution\n";
        std::cerr << std::fixed << std::setprecision(5) << "old cost:\t" << mx_cost << '\n';
        std::cerr << std::fixed << std::setprecision(5) << "new cost:\t" << my_cost << '\n';
        fout << std::fixed << std::setprecision(11) << my_cost << '\n';
        fout.close();

        return true;
    } else {
        return false;
    }
}

void MockSignals() {
    static bool is_mocked = false;

    if (is_mocked) {
        return;
    }

    is_mocked = true;
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = EnsureNiceRelease;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

void Dump(BaseOutput& output) {
    MockSignals();

    num_dump_calls += 1;
    if ((num_dump_calls & (-num_dump_calls)) == num_dump_calls) {
        std::cerr << "Called dump #" << num_dump_calls << " times\n";
    }

    struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, getpid()};
    int fd;

    if ((fd = open(LockFile().c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        exit(1);
    }

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    dumping = true;

    // command here
    if (CheckUpgrade(output)) {
        auto fout = GetAnsStream();
        output.Dump(fout);
        fout.close();
    }

    fl.l_type = F_UNLCK; /* set to unlock same region */

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    close(fd);
    dumping = false;

    if (to_be_killed) {
        exit(0);
    }
}

