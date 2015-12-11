//Problem #A from Codeforces MindCodingFinal2
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#define fi first
#define se second
#define int64 long long

map<string, string> val;




char txt[1000];
int st = 0;

void str() {
	string aux = "";
	while (st < int(strlen(txt)) and txt[st] != ',') {
    	char c = txt[st];
		if (c == ' ')
			;
		else
			aux += c;
		++st;
	}
	++st;
	cout << val[aux];
}
void flo(int p) {
 	string aux = "";
	while (st < int(strlen(txt)) and txt[st] != ',') {
    	char c = txt[st];
		if (c == ' ')
			;
		else
			aux += c;
		++st;
	}
	++st;
	string rez = val[aux];
	double x = 0.0;
	int ind = 0;
	while (ind < rez.size() and rez[ind] != '.') {
		x *= 10.0;
		x += rez[ind] - '0';
		++ind;
	}
	++ind;
	double e = 0.1;
	while (ind < rez.size()) {
		x += e * (rez[ind] - '0');
		++ind;
		e *= 0.1;
	}
	if (p == 1)
		printf("%.1f", x + e * 0.5);
	if (p == 2)
		printf("%.2f", x + e * 0.5);
 	if (p == 3)
		printf("%.3f", x + e * 0.5);   	
 	if (p == 4)
		printf("%.4f", x + e * 0.5);   	
 	if (p == 5)
		printf("%.5f", x + e * 0.5);   	
 	if (p == 0)
		printf("%.0f", x + e * 0.5);   	
 	if (p == 6)
		printf("%.6f", x + e * 0.5);   	
}

void number(int p) {
	string aux = "";
	while (st < int(strlen(txt)) and txt[st] != ',') {
    	char c = txt[st];
		if (c == ' ')
			;
		else
			aux += c;
		++st;
	}
	++st;
	string rez = val[aux];
	string rez2 = "";
	for (int i = 0; i < p; ++i)
		rez2 += ' ';
	int ind = int(rez.size()) - 1;
	for (int i = int(rez2.size()) - 1; ind >= 0; --ind, --i) {
		rez2[i] = rez[ind];
	}
	for (int i = 0; i < p; ++i)
		cout << rez2[i];
}                  

int main() {
	int n;
	cin >> n;
	while (n--) {
		cin >>txt;
		string a, b;
 		int ind = 0;
		while (txt[ind] != '=') {
        	a += txt[ind];
			++ind;
		}
		ind++;
		while (ind < int(strlen(txt))) {
	    	b += txt[ind];
			++ind;
		}
		val[a] = b;
	}
	char c;
	int ind = 0;
	scanf("%c", &c);
	scanf("%c", &c);
	while (c != '\n') {
		txt[ind] = c;
		txt[ind + 1] = '\0';
		ind++;
		scanf("%c", &c);
	}
	st = 0;
	while (st < int(strlen(txt)) and txt[st] != ',')
		++st;
	++st;
 	for (int i = 0; i < int(strlen(txt)) and txt[i] != ','; ++i) {
		if (txt[i] == '%') {
        	if (txt[i + 1] == 's') {
				str();
				i += 1;
				continue;
			}
			if (txt[i + 1] == '.') {
				flo(txt[i + 2] - '0');
				i += 3;
				continue;
			}
			if (txt[i + 1] != 's' and txt[i + 1] != '.')  {
				number(txt[i + 1] - '0');
				i += 2;
				continue;
			}
		} else
			cout << txt[i];
	}
	return 0;
}

