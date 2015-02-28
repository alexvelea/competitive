//Problem B from Codeforces Round 282
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, Mod = 1000000007, kMaxN = 100005;

string a, b, txt;

int kmp[kMaxN];
int shit_end_here[kMaxN], sum_shit_end_here[kMaxN], uniq_shit[kMaxN], sum2_shit_end_here[kMaxN];

int main() {

    cin >> txt;
	a = ' ';
	a += txt;

	
	cin >> txt;
	b = ' ';
	b += txt;

	int k = 0;
 	for (int i = 2; i < b.size(); ++i) {
		while (k && b[k + 1] != b[i])
			k = kmp[k];
		if (b[k + 1] == b[i])
			++k;
		kmp[i] = k;
	}
	
//cerr << a.size() << '\n';
	shit_end_here[0] = sum_shit_end_here[0] = 0;

	for (int i = 1, k = 0; i < a.size(); ++i) {
		while (k && a[i] != b[k + 1])
			k = kmp[k];
		if (a[i] == b[k + 1])
			++k;
		if (k == b.size() - 1) {
			if (i == k)
				shit_end_here[i] = 1;
			else
				shit_end_here[i] = sum2_shit_end_here[i - b.size() + 1] - uniq_shit[i - 1] + 
				i - b.size() + 2;
			k = kmp[k];
		}


     	if (shit_end_here[i] >= Mod)
			shit_end_here[i] -= Mod;   	
      	if (shit_end_here[i] >= Mod)
			shit_end_here[i] -= Mod;   	   		
     	if (shit_end_here[i] < 0)
			shit_end_here[i] += Mod;   		

 		uniq_shit[i] = uniq_shit[i - 1] + shit_end_here[i];

        if (uniq_shit[i] >= Mod)
			uniq_shit[i] -= Mod;

		shit_end_here[i] += shit_end_here[i - 1];
    	if (shit_end_here[i] >= Mod)
			shit_end_here[i] -= Mod;

		sum_shit_end_here[i] = shit_end_here[i] + sum_shit_end_here[i - 1];
		if (sum_shit_end_here[i] >= Mod)
			sum_shit_end_here[i] -= Mod;

		sum2_shit_end_here[i] = sum2_shit_end_here[i - 1] + sum_shit_end_here[i];
 		if (sum2_shit_end_here[i] >= Mod)
			sum2_shit_end_here[i] -= Mod;

//		cerr << i << '\t' << shit_end_here[i] << '\t' << sum_shit_end_here[i] << '\t' << uniq_shit[i] << '\t' << sum2_shit_end_here[i] << '\n';
	}
	int R = 0;
	for (int i = 1; i < a.size(); ++i) {
		R += shit_end_here[i];
		if (R >= Mod)
			R -= Mod;
	}
	cout << R;
	return 0;
}
