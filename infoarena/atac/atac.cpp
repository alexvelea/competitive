#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_n  100005
#define max_log 22
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define INF 0x3f3f3f3f

pair<int,int> Ancestor[max_n][max_log];
vector< pair<int,int> > Vertex[max_n];
vector<int> Rez;
int RMQ[max_n][max_log];
int Deep[max_n],First[max_n],nr;
bool Viz[max_n];

int i,j,n,m,p;
int x,y,A,B,C,D;
int rez,target;

void make_rmq(){
	int i,l;
	for( l=1; (1<<l)<=nr; ++l ){
		for( i=1; i+(1<<l)-1<=nr; ++i ){
			RMQ[i][l]=min(RMQ[i][l-1],RMQ[i+(1<<(l-1))][l-1]);
		}
	}
	for( l=1; (1<<l)<=n; ++l ){
		for( i=1; i<=n; ++i ){
			Ancestor[i][l].fi=Ancestor[ Ancestor[i][l-1].fi ][l-1].fi;
			Ancestor[i][l].se=min(Ancestor[i][l-1].se, Ancestor[ Ancestor[i][l-1].fi ][l-1].se);
		}
	}
	return ;
}

void df( int nod ){
	Viz[nod]=1;
	RMQ[++nr][0]=Deep[nod];
	First[ nod ] = nr;
	FORIT( it, Vertex[nod] ){
		if(!Viz[it->fi]){

			Ancestor[it->fi][0].fi=nod;
			Ancestor[it->fi][0].se=it->se;
			Deep[it->fi]=1+Deep[nod];

			df( it->fi );
			RMQ[++nr][0]=Deep[nod];
		}
	}
}

int query( int a, int b ){
	int d,l;
	if( a > b )
		swap(a,b);
	d=b-a+1;
	l=0;
	while( (1<<l) <= d )
		++l;
	--l;
	return min( RMQ[a][l], RMQ[b-(1<<l)+1][l] );
}
int get_down( int nod, int p ){
	int rez=INF,l;
	for( l=0; l<23; ++l ){
		if( p&(1<<l) ){
			rez=min(rez,Ancestor[nod][l].se);
			nod=Ancestor[nod][l].fi;
		}
	}
	return rez;
}

int main(){
	int a,b;
	freopen("atac.in","r",stdin);
	freopen("atac.out","w",stdout);
	scanf("%d %d %d", &n, &m, &p );
	for( i=2; i<=n; ++i ){
		scanf("%d %d", &a, &b );
 		// drum de la a la i cu costul b
		Vertex[a].pb(mp(i,b));
		Vertex[i].pb(mp(a,b));
	}
	scanf("%d %d %d %d %d %d", &x, &y, &A, &B, &C, &D );
	Deep[1]=1;
	df(1);
	make_rmq();
	int l=0;
	int aux = m;
	for( ; m; --m ){
		// facem pt x,y
		target = query( First[x], First[y] );
 		rez=get_down( x, Deep[x]-target );
		rez=min( rez, get_down( y, Deep[y]-target ) );
		if( rez == INF )
			rez = 0;
        Rez.pb(rez);
		x=((1LL*x*A+1LL*y*B)%n)+1;
		y=((1LL*y*C+1LL*rez*D)%n)+1;
	}
	m=aux;
	for( i=m-p; i<m; ++i )
		printf("%d\n",Rez[i]);
	return 0;
}
