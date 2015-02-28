#include<cassert>

#include<algorithm>
#include <iostream>
#include<vector>
#include<stack>
using namespace std;

const int kMaxN = 2005;

const int kBufferSize = 1000005;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (cin.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;
	
	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
    
	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}


bool InQ[kMaxN], edge[kMaxN][kMaxN];

int nrCtc=0;
int Deep[kMaxN], Low[kMaxN], deep;
stack<int> Stack;

int n, m, a, b, i;

void get_min(int &a, int b) {
    if (a > b)
        a = b;
}

void tarjan( int nod ){
    if( Deep[nod] )
        return ;
    Stack.push( nod );
    InQ[nod]=true;
    Deep[nod]=++deep;
    Low[nod]=deep;
    for (int itr = 1; itr <= n; ++itr) {
        if(edge[nod][itr] and !Deep[itr]){
            tarjan (itr);
            get_min (Low[nod], Low[itr]);
        }else
            if (edge[nod][itr] and InQ[itr])
                get_min (Low[nod], Low[itr]);
    }
    if (Deep[nod] == Low[nod]){
        bool ok = true;
        nrCtc++;
        while( ok ){
            InQ[Stack.top()] = false;
            if (nod == Stack.top())
                ok=false;
            Stack.pop();
        }
    }
    return ;
}

int main(){
    cit(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int el;
            cit(el);
            if (el != 0) {
                edge[i][j] = true;
            }
        }
    
    for (i=1; i<=n; ++i)
        if (!Deep[i]) {
            tarjan(i);
            assert(Stack.empty());
        }
    if (nrCtc == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
