#include <cassert>

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define max_n 100005
#define max_m 500005
#define pb push_back

ifstream in("dans.in");
ofstream out("dans.out");

const int kBufferSize = 10000;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (in.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

int el[max_m];

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


bool VizEdge[max_m];

struct edge{
    int a,b,ind;
    edge(){
        a=b=ind=0;
    }
    edge( int _a, int _b, int _ind ){
        a=_a;
        b=_b;
        ind=_ind;
		VizEdge[ind] = 0;
    }
    int other( int nod ){
        return a+b-nod;
    }
    int viz(){
        return VizEdge[ind];
    }
    void setViz(){
        VizEdge[ind]=1;
    }
} Edge[max_m];
vector<int> Vertex[max_n], Rez;
int St[max_m + max_n];

int n,i;
int It[max_n];

int main(){
int m,a,b;
int t;
cit(t);
while (t--) {
	cit(n);
	cit(m);

	for (int i = 1; i <= n; ++i)
		Vertex[i].clear();
	Rez.clear();


    for (i=1; i<=m; ++i) {
        cit(a);
		cit(b);
		Vertex[a].pb(i);
        Vertex[b].pb(i);
        Edge[i]=edge(a,b,i);
    }
   	for (int i = 1; i <= n; ++i)
		It[i] = 0;

    int st = 0;
	int bad = 0;
	for (int i = 1; i <= n; ++i)
		if (Vertex[i].size() % 2 == 1) {
			++bad;
			St[bad] = i;
		}
	if (bad > 2) {
		out << "NU\n";
		continue;
	}

	if (m == 0) {
		out << "DA\n";
		continue;
	}

	int Start = 1;
	while (Start <= n and Vertex[Start].size() == 0)
		++Start;
	
	if (bad == 0) {
		St[1] = Start;
	} else {
		m++;
		Edge[m] = edge(St[1], St[2], m);
		Vertex[St[1]].push_back(m);
		Vertex[St[2]].push_back(m);
	}
	st = 1;
    bool ok;
	Rez.clear();
    while (st) {
        ok = 1;
		int nod = St[st];
        for ( ;It[nod] < int(Vertex[nod].size()); ) {
			int mu = Vertex[nod][It[nod]];
			++It[nod];
            if (!Edge[mu].viz()) {
                Edge[mu].setViz();

				++st;
                St[st] = Edge[mu].other(nod);
                ok = 0;
                break;
            }
        }
        if (ok) {
            Rez.pb(nod);
        	--st;
		}
    }
	bool K = true;
	for (int i = 1; i <= n; ++i) {
		if (It[i] != Vertex[i].size()) {
			out << "NU\n";
 			K = false;   		
			break;
		}
	}
	if (K) {
		el[0] = 1;
		el[1] = Rez[0];
		out << "DA\n" << Rez[0] << ' ';

	    for (i = Rez.size() - 2; i; --i) {
			out << Rez[i] << ' ';
			el[++el[0]] = Rez[i];
		}
		if (bad == 0) {
			out << Start;
	  	  	el[++el[0]] = Start;
		}
		out << "\n";
//		cerr << el[0] << '\n';
		assert(el[0] == 1 + m - (bad / 2));
	}
}
    return 0;
}
