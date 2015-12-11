#include <cstdio>
#include <iostream>
using namespace std;

	#define BufferSize 1000000
	#define verf ((++CharC==BufferSize)?(cin.read(Buffer,BufferSize),CharC=0):(0))
	int CharC;
	char Buffer[BufferSize+5];
	void cit ( int &a ){
		for ( ; !( ( Buffer[CharC]>='0' && Buffer[CharC]<='9' ) || ( Buffer[CharC]=='-' ) ); verf )
			;
		int minus=0;
		if ( Buffer[CharC] == '-' ){
			minus=1;
			verf;
		}
		a=0;
		for ( ; ( ( Buffer[CharC]>='0' && Buffer[CharC]<='9' ) || ( Buffer[CharC]=='-' ) ); verf ){
			a*=10;
			a+=Buffer[CharC]-'0';
		}
		if ( minus )
			a*=-1;
		return ;
	}


	#define INF 5001200
	#define max_n 20000105
	int Deq1[max_n],Deq2[max_n],St[max_n],Dr[max_n];
	int n,a,b,aux,i;
	long long rez;

void solve ( int x, int y ){
	int st1=1,dr1=1;
	int st2=1,dr2=1;
	int i;
	St[0]=INF;
	Dr[0]=-1;
	Deq1[1]=1;
	Deq2[1]=1;
	for ( i=2; i<=x; i++ ){
		while ( St[ Deq1[dr1] ] < St[i] )
			dr1--;
		Deq1[++dr1]=i;
	}
	for ( i=2; i<=x; i++ ){
		while ( Dr[ Deq2[dr2] ] > Dr[i] )
			dr2--;
		Deq2[++dr2]=i;
	}
	for ( i=x; i<=n; i++ ){
    	// verificam pentru x
		if ( St[ Deq1[st1] ] + y - 1 <= Dr[ Deq2[st2] ] )
			rez+= Dr[ Deq2[st2] ] - St[ Deq1[st1] ] - y + 2;
 		if ( Deq1[st1] == i-x+1 )
			st1++;
        if ( Deq2[st2] == i-x+1 )
			st2++;
		// adaugam elementul nou
		while ( (dr1>=st1) && ( St[ Deq1[dr1] ] < St[i+1] ) ){
			dr1--;
		}
		Deq1[++dr1]=i+1;
		while ( (dr2>=st2) && ( Dr[ Deq2[dr2] ] > Dr[i+1] ) ){
			dr2--;
		}
		Deq2[++dr2]=i+1;
	}
	return ;
}

int main(){

		freopen ("drept2.in","r",stdin);
		freopen ("drept2.out","w",stdout);

	verf;
    cit(n);
	cit(n);
	cit(a);
	cit(b);
	cit(St[1]);
	cit(Dr[1]);
	for ( i=2; i<=n; i++ ){
		cit(St[i]);
		cit(aux);
		Dr[i]=Dr[i-1]+aux;
	}
	for ( i=1; i<=n; i++ ){
		Dr[i]=Dr[i]+St[i]-1;
	}
	solve ( a,b );
	solve ( b,a );
	if ( a == b )
		rez/=2;
	cout<<rez;
	return 0;
}
