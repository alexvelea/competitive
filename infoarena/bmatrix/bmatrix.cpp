#include <cstdio>
#include <algorithm>
using namespace std;

	#define max_n 205

	int n,m,i,j,maxim=0;
	char c;
	bool T[max_n][max_n];

	int Up[max_n],St[max_n],Dr[max_n],Rez[2][max_n];
	int Deq[max_n],last,first;

void rotate (){
	int i,j;
	int TP[max_n][max_n];
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			TP[j][n-i+1]=T[i][j];
			T[i][j]=0;
		}
	}           
	swap ( n,m );
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			T[i][j]=TP[i][j];
		}
	}
}

void solve (){
	for ( int o=0; o<2; o++ ){
		for ( i=1; i<=n; i++ )
			Rez[o][i]=0;
		for ( j=1; j<=m; j++ )
			Up[j]=0;
		for ( i=1; i<=n; i++ ){
			for ( j=1; j<=m; j++ ){
				St[j]=Dr[j]=0;
            	if ( T[i][j] )
					Up[j]=0;
				else
					Up[j]++;
			}			
			Up[0]=Up[m+1]=-1;
			first=last=0;
			Deq[last]=0;
			for ( j=1; j<=m; j++ ){
				while ( ( Up[ Deq[last] ] >= Up[j] ) && ( last >= first ) )
					last--;
				if ( !T[i][j] )
					St[j]=j-Deq[last];
				Deq[++last]=j;
			}

			first=last=0;
			Deq[last]=m+1;
			for ( j=m; j>=1; j-- ){
				while ( ( Up[ Deq[last] ] >= Up[j] ) && ( last >= first ) )
                	last--;
				if ( !T[i][j] )
					Dr[j]=Deq[last]-j;
				Deq[++last]=j;
			}                 
			Rez[o][i]=Rez[o][i-1];
			for ( j=1; j<=m; j++ ){
                Rez[o][i]=max( Rez[o][i], Up[j]*(St[j]+Dr[j]-1) );
			}
		}
		rotate();
		rotate();
	}
	for ( i=1, j=n-1; i<n; ++i,--j )
		if ( Rez[0][i]+Rez[1][j] > maxim )
			maxim = Rez[0][i]+Rez[1][j];
}
int main(){

    	freopen ("bmatrix.in","r",stdin);
		freopen ("bmatrix.out","w",stdout);

	scanf ("%d %d\n", &n, &m );
	for ( i=1; i<=n; i++ ){
    	for ( j=1; j<=m; j++ ){
			scanf("%c",&c);
			T[i][j]=c-'0';
		}
		scanf ("%c",&c);
	}

	solve();
	// rotim invers 
 	rotate();
	solve();
	printf("%d\n",maxim);
	return 0;
}
