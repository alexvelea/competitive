#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define max_n 1005
#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

vector<int> Vertex[max_n];
int Best[max_n][max_n][2];
int Rez[max_n][2];
int Father,i,n;

void get_max( int &a, int b ){
	if( b>a )
		a=b;
}

void df( int nod ){
	int i,j,l,n,ind;
	FORIT( it, Vertex[nod] )
		df(*it);
	sort( Vertex[nod].begin(), Vertex[nod].end() );
	// cazul in care nu luam nodul actual :)
	n=Vertex[nod].size();
	for( i=0; i<=n+2; ++i )
		for( j=0; j<=n+2; ++j )
			Best[i][j][0]=Best[i][j][1]=0;
	for( i=0; i<n; ++i )
		Best[i][i][0]=max(Rez[Vertex[nod][i]][0], Rez[Vertex[nod][i]][1] );
	for( l=1; l<n; ++l ){
		for( i=0; i+l<n; ++i ){
			j=i+l;
 			get_max( Best[i][j][0], Best[i+1][j][0]+Best[i][i][0] );
			if( j>0 ) get_max( Best[i][j][0], Best[i][j-1][0]+Best[j][j][0] );
			if( j>0 ) get_max( Best[i][j][0], Best[i+1][j-1][0]+Rez[Vertex[nod][i]][0]+Rez[Vertex[nod][j]][0]+abs(Vertex[nod][i]-Vertex[nod][j]));
		}
	}
	Rez[nod][0]=Best[0][n-1][0];
	// il luam si pe a nostru :)
	Vertex[nod].push_back(nod);
	sort(Vertex[nod].begin(),Vertex[nod].end());
	n=Vertex[nod].size();
	        	
    for( i=0; i<n; ++i )
		if( Vertex[nod][i] == nod ) 
			ind=i;
	for( i=0; i<=n; ++i ){
		for( j=0; j<=n; ++j ){
			Best[i][j][1]=-2;	
		}
	}
	for( i=ind+1; i<n; ++i ){
		Best[ind][i][1]=Rez[Vertex[nod][i]][0]+abs(Vertex[nod][ind]-Vertex[nod][i]);
		if( i-2>=0 )
			Best[ind][i][1]+=Best[ind][i-2][0];
	}
	for( i=ind-1; i>=0; --i ){
		Best[i][ind][1]=Rez[Vertex[nod][i]][0]+abs(Vertex[nod][ind]-Vertex[nod][i]);
		if( ind-1 >= 0 )
			Best[i][ind][1]+=Best[i+1][ind-1][0];
	}
	Best[ind][ind][1]=-2;
	for( l=1; l<n; ++l ){
		for( i=0; i+l<n; ++i ){
			j=i+l;
			// ne putem extinde
			// contine elementul ala cheie.
			if( Best[i+1][j][1]!=-2 )
				get_max(Best[i][j][1],Best[i+1][j][1]+max(Rez[Vertex[nod][i]][0],Rez[Vertex[nod][i]][1]));
			if( Best[i][j-1][1]!=-2 )
				get_max(Best[i][j][1],Best[i][j-1][1]+max(Rez[Vertex[nod][j]][0],Rez[Vertex[nod][j]][1]));
			if( Best[i+1][j-1][1] != -2 )
				get_max(Best[i][j][1], Best[i+1][j-1][1] + Rez[Vertex[nod][i]][0] + Rez[Vertex[nod][j]][0] + abs( Vertex[nod][i]-Vertex[nod][j]));
		}
	}
	Rez[nod][1]=max(Best[0][n-1][1],0);
//    printf("%d\t%d\t%d\n",nod,Rez[nod][0],Rez[nod][1]);
}

int main(){
	freopen("petsoft.in","r",stdin);
	freopen("petsoft.out","w",stdout);
	scanf("%d", &n );
	for( i=2; i<=n; ++i ){
		scanf("%d", &Father);
		Vertex[Father].pb(i);
	}
	df(1);
	printf("%d\n",max(Rez[1][0],Rez[1][1]));
	return 0;
}
