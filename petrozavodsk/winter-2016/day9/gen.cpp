#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

string ReadFromFile(const string& file) {
    ifstream fin(file);
    string aux, result; 
    while (fin >> aux) {
        result += aux;
        result += " ";
    }
    fin.close();
    return result;
}

void WriteToFile(const string& file, const string& content) {
    ofstream fout(file);
    fout << content << '\n';
    fout.close();
}

string TestData() {
    int t = 10;
    string s = "";
    while (t--) {
    int n = rand() % 50 + 4;
    vector<int> p;
    vector<int> o;
    for (int i = 1; i <= n; i += 1) {
        p.push_back(i);
    }

    for (int i = 1; i <= 4; i += 1) {
        o.push_back(i);
    }

    random_shuffle(o.begin(), o.end());
    random_shuffle(p.begin(), p.end());
/*    
    string s = to_string(n) + "\n";
    for (int i = 0; i < 4 * n + 1; i += 1) {
        s += to_string(rand() % maxVal + 1);
        s += " ";
    }
*/
    s += to_string(n) + '\n';
    for (auto itr : p) {
        s += to_string(itr) + ' ';
    }
    s += '\n';
    for (auto itr : o) {
        s += to_string(itr) + " ";
    }
    s += '\n';
    }

    return s;
}

void RunAndShit(const string& content) {
    WriteToFile("in", content);
    system("./_h2 <in >out 2>/dev/null");
    auto a = ReadFromFile("out");

    system("./_h_brut <in >out 2>/dev/null");
    auto b = ReadFromFile("out");

    if (a != b) {
        cerr << "Fail\n";
        exit(0);
    }   
}

string AllShits(int n) {
    string s;
    vector<int> ord(4);
    for (int i = 0; i < 4; i += 1) {
        ord[i] = i;
    }
    while (next_permutation(ord.begin(), ord.end())) {
        vector<int> perm(n);
        for (int i = 0; i < n; i += 1) perm[i] = i;
        while (next_permutation(perm.begin(), perm.end())) {
//            string s = "";
            s += to_string(n) + '\n';
            for (auto itr : perm) {
                s += to_string(itr + 1) + ' ';
            }
            s += '\n';
            for (auto itr : ord) {
                s += to_string(itr + 1) + " ";
            }
            s += '\n';

//            RunAndShit(s);
        }
    }

    return s;
}

int main() {
    srand(time(NULL));
    int T = 1;
    for (int t = 0; t < T; t += 1) {
        if (t % 10 == 0) {
            cerr << t << "\n";
        }
//        RunAndShit(TestData());
        RunAndShit(AllShits(7));
    }
}
