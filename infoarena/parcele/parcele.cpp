#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

	#define max_n 100105

	int xc,yc;
	int n,i,maxim;
	int RezSt[max_n], RezDr[max_n];

	struct arbore {
		int val, max;
	} A[(1<<18)];

	struct point {
		int x,y;
	}	T[max_n],aux;
	bool mysort ( point a, point b ){
		return a.y <b.y;
	}

	int max ( int a, int b){
		if ( a > b )
			return a;
		return b;
	}                                       
	int min ( int a, int b ){
		if ( a < b )
			return a;
		return b;
	}

void update ( int a, int b, int st, int dr, int nod, int val ){
	if ( a == st && b == dr ){
		A[nod].val+=val;
	}
	else{
		int m=(st+dr)/2;
		if ( a <= m && m+1<=b ){
			// split
	 		update ( a,m, st,m, 2*nod, val );
			update ( m+1, b, m+1, dr, 2*nod+1, val );
		}		
		else {
			if ( b<=m ){
				update ( a,b,st,m,2*nod,val);
			}
			else {
				if ( m+1<=a ){
					update ( a,b,m+1,dr,2*nod+1,val);
				}
			}
		}
	}
	if ( st == dr )
		A[nod].max = A[nod].val;
	else
		A[nod].max = max ( A[2*nod].max, A[2*nod+1].max ) + A[nod].val;
	return ;
}

void re2 ( ){	
	int ist=1,idr=1,j;
	for ( ; idr<=n; ){
		while ( (T[ist].y <= T[idr].y-yc-1) && ( ist<=n ) ){
            RezSt[ist]=A[1].max;
			update ( T[ist].x,  min(T[ist].x+xc,max_n) , 1, max_n, 1, -1 );
			ist++; 	
		}           
		j=idr;
		while ( T[idr].y == T[j].y && idr<=n ){
			update ( T[idr].x, min(T[idr].x+xc,max_n) , 1, max_n, 1, 1 );
			idr++;
		}
		for ( ; j<idr; j++ ){
			RezDr[j] = A[1].max;
		}	                 			
	}
	for ( ; ist<=n; ist++ ){
		RezSt[ist]=A[1].max;                                                                     	
		update ( T[ist].x, min(T[ist].x+xc,max_n), 1, max_n, 1, -1 );
	}
	return ;
}

int AA[max_n],BA[max_n];
void re1(){
	sort ( T+1, T+n+1, mysort );
	re2();
	int ist=1,idr=1,i;
	AA[0]=0;
	for ( i=1; i<=n; i++ ){
    	AA[i]=max(AA[i-1],RezDr[i]);      
	}
	BA[n+1]=0;
	for ( i=n; i>=1; i-- ){
		BA[i]=max(BA[i+1],RezSt[i]);
	}
	for ( ; ist<=n; ist++ ){
		while ( ( idr<=n ) && ( T[ist].y == T[idr].y ) )
			idr++;
		if ( maxim < AA[ist]+BA[idr] )
			maxim=AA[ist]+BA[idr];			
	}
}         

int main(){
	

		freopen ("parcele.in","r",stdin);
		freopen ("parcele.out","w",stdout);

	
	scanf ("%d %d", &xc, &yc );
	scanf ("%d", &n );
	if ( n == 1 ){
		printf("1\n");
		return 0;
	}
	for ( i=1; i<=n; i++ ){
		scanf ("%d %d", &T[i].x, &T[i].y);
		T[i].x++;                         
		T[i].y++;
	}
	re1();	
    for ( i=1; i<=n; i++ ){
		swap ( T[i].x, T[i].y );
	}                  
	swap(xc,yc);
	re1( );
	printf("%d\n",maxim);
	return 0;	
}
