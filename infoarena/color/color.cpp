#include <fstream>
using namespace std;

const int max_n = 4005;

long long rez = 0;
int Edge[max_n];

ifstream in("color.in");
ofstream out("color.out");

#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    bool ok=0;
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
    if ( Buffer[ CharB ] == '-' ){
        verf;
        ok=1;
    }
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}

int main() {
    verf;
	int n, m;
    cit (n);
    cit (m);
	if (n < 3) {
		out << "0\n";
		return 0;
	}
	while (m--) {
		int a, b;
        cit (a);
        cit (b);
		Edge[a]++;
		Edge[b]++;
	}
	for (int i = 1; i <= n; ++i) 
		rez += Edge[i] * (n - 1 - Edge[i]);
	rez /= 2;
	out << 1LL * n * (n-1) * (n-2) / 6 - rez << '\n';
	return 0;
}
