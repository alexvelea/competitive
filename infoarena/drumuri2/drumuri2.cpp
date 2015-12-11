#include <cstdio>

#include <iostream>
#include <vector>

using namespace std;

#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n=105, max_m=5005;

vector<int> Order, Vertex[max_n], VertexDown[max_n];
int n, m;
int i, j;
int a, b, Link[max_n];
bool Viz[max_n];

void Topo( int nod ){
    if( Viz[i] )
        return ;
    Viz[nod] = true;
    FORIT( it, Vertex[nod] )
    Topo( *it );
    Order.push_back( nod );
    return ;
}

int FindDown( int nod ){
    FORIT( it, VertexDown[nod] )
    if( !Link[*it] )
        return *it;
    return 0;
}

void GoDown( int nod, int target ){
    if( Viz[nod] )
        return ;
    Viz[nod] = true;
    FORIT( it, Vertex[nod] )
    GoDown( *it, target );
    if( nod != target )
        VertexDown[target].push_back( nod );
    return ;
}

bool FindAugPath( int nod ){
    if( Viz[nod] )
        return false;
    Viz[nod] = true;
    int down = FindDown( nod );
    if( down ){
        Link[down] = nod;
        return true;
    }
    FORIT( it, Vertex[nod] )
    if( FindAugPath(Link[*it]) ){
        Link[*it] = nod;
        return true;
    }
    return false;
}

int main(){
    freopen("drumuri2.in","r",stdin);
    freopen("drumuri2.out","w",stdout);
    scanf("%d %d", &n, &m );
    for( i=1; i<=m; ++i ){
        scanf("%d %d", &a, &b );
        Vertex[a].push_back( b );
    }
    for( i=1; i<=n; ++i )
        Topo( i );
    for( i=1; i<=n; ++i ){
        for( j=1; j<=n; ++j )
            Viz[j] = false;
        GoDown( i, i );
    }
    int Rez = 0, nod;
    for( i=0; i<n; ++i ){
        nod = Order[i];
        //      cerr<<nod<<"\n";
        //      cerr<<"\n";
        for( j=1; j<=n; ++j )
            Viz[j] = false;
        if( FindAugPath( nod ) )
            ;
        else
            Rez++;
    }
    printf("%d\n", Rez );
    return 0;
}
