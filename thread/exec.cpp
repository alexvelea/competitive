#include <iostream>
#include <thread>
using namespace std;

int Wait() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cerr << "EXIT!\n";
    exit(0);
    return 0;
}

int exec() {
    system("./inf");
}

int main() {
    thread t;
    t = thread(Wait);
    system("./inf");
    t.join();
    return 0;    
}
