#include <cmath>
#include <cstdio>
#include <cstring>

#include <iostream>

using namespace std;

	#define max_n 1005
	#define max_l 1000005

char Mat[ max_n ][ max_n ];
char Text[ max_l ];
int i,j,n;

void solve ( int stx, int sty, int drx, int dry, int c1, int c2 ){
//	cerr<<c1<<"\t"<<c2<<"\n";
	if ( Text[ c1 ] != '*' ){
		// avem doar un singur fel de caracter.
		for ( int i=sty; i<=dry; ++i )
			for ( int j=stx; j<=drx; ++j )
				Mat[i][j]=Text[c2];
		return ;
	}
	int midx=(stx+drx)/2 ,midy=(sty+dry)/2;
    int	Count[5];
	int A[5];
	c1++;
	Count[1]= (midx-stx+1)*(midy-sty+1);
	Count[2]= (drx-midx)*(midy-sty+1);
	Count[3]= (midx-stx+1)*(dry-midy);
	Count[4]= (drx-midx)*(dry-midy);
	A[1]=A[2]=A[3]=A[4]=0;

	int CSt[6],CDr[6];
	CSt[1]=c1;
    int p=1;
	for ( ; c1<=c2; ++c1 ){
 		int nr=0;
		while ( Text[ c1 ] >= '0' && Text[ c1 ]<='9' ){
			nr*=10;
            nr+=Text[c1]-'0';
			c1++;
		}
		if ( nr == 0 ){
			nr=1;
		}
		if ( Text[c1]>='a' && Text[c1]<='z' ){
 			A[p]+=nr;		
		}
		while ( p<=4 && A[p]==Count[p] ){
			CDr[p]=c1;
//			cerr<<CSt[p]<<" "<<CDr[p]<<" @ \n";
			CSt[p+1]=c1+1;
			p++;
		}
	}
//	printf("\n");
	if ( Count[1] ){
   		solve ( stx , sty , midx, midy, CSt[1], CDr[1] );	
	}
	if ( Count[2] ){
   		solve ( midx+1, sty, drx, midy, CSt[2], CDr[2] );
	}
	if ( Count[3] ){
   		solve ( stx , midy+1, midx, dry, CSt[3], CDr[3] );
	}
	if ( Count[4] ){
   		solve ( midx+1 , midy+1, drx, dry, CSt[4], CDr[4] );
	}
	return ;
}

int main(){

    freopen ("compresie.in","r",stdin);
	freopen ("compresie.out","w",stdout);

	scanf ("%s", &Text );
	n=strlen ( Text );

	int count=0,rez=0;
    for ( i=0; i<n; ++i ){
        if ( Text[ i ] == '*' )
			rez++;
		int nr = 0;
		while ( Text[ i ] >='0' && Text[ i ]<='9' ){
			nr*=10;
			nr+=Text[ i ] - '0';
			i++;
		}
		if ( nr == 0 )
			nr=1;
 		if ( Text[ i ] >= 'a' && Text[ i ] <='z' )
			count+=nr;
	}
	count = sqrt( count );
	solve ( 1, 1, count, count, 0, n-1 );
	printf("%d\n",rez);
	for ( i=1; i<=count; ++i ){
		for ( j=1; j<=count; ++j ){
			printf("%c", Mat[i][j]);
		}
		printf("\n");
	}
}
