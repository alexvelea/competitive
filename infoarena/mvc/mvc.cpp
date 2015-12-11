#include <cstdio>

#include <vector>

using namespace std;

	#define max_n 100005
	#define pb push_back
	#define INF 0x3f3f3f3f

	int n,i,a,b;

	vector<int> Graph[max_n];
	int Color[max_n], Cost[max_n];
	int Best[max_n][2];

	struct edge {
		int a,b;
	} Edge [max_n];
	bool Viz_Edge[max_n];
	bool Viz_Nod [max_n];

	int Rez[2],Last[2];
	int minim,start;

int min ( int a, int b ){
	if ( a < b )
		return a;
	return b;
}

int df ( int nod ){
	int from=0;
	Color[nod]=1;

	for ( int it=0; it< int ( Graph[nod].size() ); ++it ){
		if ( !Viz_Edge[ Graph[nod][it] ] ){
			Viz_Edge[ Graph[nod][it] ] = 1;

			int b = Edge [ Graph[nod][it] ].a + Edge[ Graph[nod][it] ].b - nod;
			if ( !Color[b] ){
				int aux ;
				aux = df ( b );
				if ( aux ){
					from = aux;
				}
			}
			else{
				from = b;
			}
		}
	}
	if ( from )
		Color[nod]=2;
	return from;
}

void Request ( int nod ){
	Viz_Nod[nod]=1;
	for ( int it=0; it< int ( Graph[nod].size() ); ++it ){
		int b = Edge[ Graph[nod][it] ].a + Edge[ Graph[nod][it] ].b - nod ;
		if ( ( !Color[b] ) && ( !Viz_Nod[b] ) ){
 			Request ( b );
			Best[ nod ][ 0 ] += Best [ b ][ 1 ];
			Best[ nod ][ 1 ] += min ( Best[ b ][ 1 ], Best[ b ][ 0 ] );
		}
	}
	Best[ nod ][ 1 ] += Cost[ nod ];
}

int next ( int nod ){
	for ( int i=0; i< int ( Graph[nod].size() ); ++i ){
		int b = Edge [ Graph[nod][i] ].a + Edge [ Graph[nod][i] ].b - nod ;
		if ( Color[b] && ( !Viz_Nod[b] ) ){
			return b;
		}
	}
	return -1;
}
 
void solve (){
	int i;
	start=0;
 	for ( i=1; i<=n && (!start); ++i ){
		if ( Color[i] ){
			start=i;
		}
	}
 
 	for ( i=1; i<=n; ++i ){
		Viz_Nod[i]=0;
	}
	Viz_Nod[start]=1;
	int nod=next ( start );
	Last[0]=Last[1]=0;
	while ( nod != -1 ){

		Rez[0] = Last[1]+Best[nod][0]; // nu apasam butonul curent.
		Rez[1] = min ( Last[0], Last[1] ) + Best[nod][1]; // apasam butonul curent
		Last[0]=Rez[0];
		Last[1]=Rez[1];

		Viz_Nod[nod]=1;
		nod=next(nod);
	}
 	minim = min ( Last[1], Last[0] ) + Best[ start ][ 1 ] ;

 	start=0;
 	for ( i=1; i<=n && (!start); ++i ){
		if ( Color[i] ){
			start=i;
		}
	}
 
 	for ( i=1; i<=n; ++i ){
		Viz_Nod[i]=0;
	}
	Viz_Nod[start]=1;
	nod=next ( start );
	Last[0]=Last[1]=0;
	Last[1]=INF;
	while ( nod != -1 ){

		Rez[0] = Last[1]+Best[nod][0]; // nu apasam butonul curent.
		Rez[1] = min ( Last[0], Last[1] ) + Best[nod][1]; // apasam butonul curent
		Last[0]=Rez[0];
		Last[1]=Rez[1];
		Viz_Nod[nod]=1;
		nod=next(nod);
	}
	minim = min ( Last[1] + Best[ start ][ 0 ] , minim );

 
}
int main(){
	freopen ("mvc.in","r",stdin);
	freopen ("mvc.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &Cost[i] );
	}
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &a, &b );
        Edge[i].a=a;
		Edge[i].b=b;
		Graph[a].pb(i);
		Graph[b].pb(i);
	}
	df ( 1 );
	for ( i=1; i<=n; ++i ){
		Viz_Edge[i]=0;
		if ( Color[i]==2 ){
			Color[i]=1;
		}
		else{
			Color[i]=0;
		}
	}
	for ( i=1; i<=n; ++i ){
		if ( Color[i] )
			Request( i );
	}
	solve();
	printf("%d",minim);
	return 0;
}
