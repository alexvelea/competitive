#include <cstdio>
#include <iostream>
using namespace std;

	int Deq[3000000];
	int x,a,front,back,i,n,m,dir;


#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
	int ok=0;
    if ( Buffer[ CharB] == '-' ){
		CharB++;
		ok=1;
	}
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
	if ( ok )
		a*=-1;
}


int main(){
	freopen ("carti3.in","r",stdin);
	freopen ("carti3.out","w",stdout);
	verf;
	cit(m);
	cit(n);    
	front=1500005;
	back=1500004;
	for ( i=1; i<=n; i++ ){
		cit(a);
		Deq[--front]=a;
	}
	dir=0;
	for ( i=1; i<=m; i++ ){
		cit(x);
		if ( x == -1 )
			dir^=1;
		else{   
			if ( dir == 0 ){
				Deq[++back]=x;
			}
			else{
				Deq[--front]=x;
			}
		}
	}
	if ( dir )
		for ( i=front; i<=back; i++ )
			cout<<Deq[i]<<"\n";
	else
		for ( i=back; i>=front; i-- )
			cout<<Deq[i]<<"\n";
	return 0;
}
