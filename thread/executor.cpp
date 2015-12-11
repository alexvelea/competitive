#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void wait(double time) {
    time_t t = clock();
    while (clock() - t < time * CLOCKS_PER_SEC) ;
    return ;
}

thread waitThread;
bool finishedExecution(false);

void diff(time_t &t) {
    cerr << "Time:\t" << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n';
}

void timeLimit(double time) {
    this_thread::sleep_for(chrono::milliseconds(int((time + 1.05) * 1e3)));
    if (not finishedExecution) {
        cerr << "TLE\n";
        exit(0);
    }
}

void executeProgram(string programName) {
    time_t t = clock();
    programName = "time ./" + programName;
    cerr << programName << '\n';
    system(programName.c_str());
    diff(t);
    finishedExecution = true;
}

int main(int argc, char** _argv) {
    vector<string> argv(max(argc, 8));
    for (int i = 0; i < argc; ++i) {
        argv[i] = string(_argv[i]); 
    }
    // 0 current file
    // 1 execution file
    // 2 timeLimit
    
    // 3 target input file
    // 4 test input file
    
    // 5 target output file
    // 6 test ok file
 
    // 7 verif file

    {string sys = "touch " + argv[3];
    system(sys.c_str());}

    {string sys = "cp " + argv[4] + ' ' + argv[3];
    system(sys.c_str());}

    {waitThread = thread(timeLimit, atoi(argv[2].c_str()));}

    executeProgram(argv[1]);
    return 0;
}
