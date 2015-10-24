#include "grader.h"
#include "scales.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> targetState(6, 0), whereIsInState(6, 0);
bool isInitialised = false;

int nrOfSteps;
bool isBad, testcaseIsCorrect;

bool mySort(int a, int b) {
    return whereIsInState[a] < whereIsInState[b];
}

int getLightest(vector<int> el) {
    ++nrOfSteps;
    std::sort(el.begin(), el.end(), mySort);
    return el[0];
}

int getMedian(vector<int> el) {
    ++nrOfSteps;
    sort(el.begin(), el.end(), mySort);
    return el[1];
}

int getHeaviest(vector<int> el) {
    ++nrOfSteps;
    sort(el.begin(), el.end(), mySort);
    return el[2];
} 

int getNextLightest(vector<int> el) {
    ++nrOfSteps;
    int q = el[3];
    sort(el.begin(), el.end(), mySort);
    
    if (el[3] == q) {
        return el[0];
    } else {
        for (int i = 0; i < 3; ++i) {
            if (el[i] == q) {
                return el[i + 1];
            }
        }
    }
    return 0;
}

void answer(vector<int> el) {
    if (el.size() != targetState.size()) {
        return ;
    }

    for (int i = 0; i < int(el.size()); ++i) {
        if (el[i] != targetState[i]) {
            return ;
        }
    }

    testcaseIsCorrect = true;
}

void nextTest(ifstream &fin) {
    targetState.clear();
    for (int i = 0; i < 6; ++i) {
        int x; fin >> x;
        targetState.push_back(x);
    }
}  

void run() {
    ifstream fin("allTests.txt"); 
    int T; fin >> T;
    init(T);

    isBad = false;
    
    while (T--) {
        nextTest(fin);
        for (int i = 0; i < 6; ++i) {
            whereIsInState[targetState[i]] = i;
        }

        nrOfSteps = 0;
        testcaseIsCorrect = false;

        orderCoins();

        if (not testcaseIsCorrect) {
            isBad = true;
        }
        cerr << nrOfSteps;
    }
}



int main() {
    run();    
}
