#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
using namespace std;
 
#define NMAX 7001
#define INF 1<<30
#define pb push_back
 
vector <int> v[NMAX];
vector < pair <int , int> > G[NMAX];
int D,viz[NMAX],p[NMAX],c[NMAX],cap[NMAX][NMAX],n;
 
void add_edges(int timp)
{
    int i,x,y;
    D=timp*n+1;
    for(i=1;i<=n;i++) {
        x=(timp-1)*n+i;
        v[x].pb(x+n);
        v[x+n].pb(x);
        cap[x][x+n]=INF;
        for(vector < pair <int , int> > :: iterator it=G[i].begin();it!=G[i].end();it++) {
            y=timp*n+(it->first);
            v[x].pb(y);
            v[y].pb(x);
            cap[x][y]=it->second;
        }
    }
}
 
int bfs()
{
    int st,dr,nod;
    memset(viz,0,sizeof(viz));
    memset(p,0,sizeof(p));
    st=1;
    dr=1;
    c[st]=0;
    viz[0]=1;
    while(st<=dr) {
        nod=c[st];
        st++;
        for(vector <int> :: iterator it=v[nod].begin();it!=v[nod].end();it++)
            if(viz[*it]==0 && cap[nod][*it]>0) {
                c[++dr]=*it;
                viz[*it]=1;
                p[*it]=nod;
                if(*it==D)
                    return 1;
            }
    }
    return 0;
}
 
int new_flow()
{
    int minim,nod,flux;
    flux=0;
    while(bfs()) {
        minim=INF;
        for(nod=D;nod!=0;nod=p[nod])
            minim=min(minim,cap[p[nod]][nod]);
        for(nod=D;nod!=0;nod=p[nod]) {
            cap[p[nod]][nod]=cap[p[nod]][nod]-minim;
            cap[nod][p[nod]]=cap[nod][p[nod]]+minim;
        }
        flux=flux+minim;
    }
    return flux;
}
 
int main ()
{
    int m,x,y,i,sum,t;
    ifstream f("algola.in");
    ofstream g("algola.out");
    f>>n>>m;
    sum=0;
    for(i=1;i<=n;i++) {
        f>>cap[0][i];
        sum=sum+cap[0][i];
        v[0].pb(i);
    }
    for(i=1;i<=m;i++) {
        f>>x>>y;
        f>>cap[x][y];
        G[x].pb(make_pair(y,cap[x][y]));
        G[y].pb(make_pair(x,cap[x][y]));
    }
    f.close();
    for(t=1;sum>=1;t++) {
        add_edges(t);
        sum=sum-new_flow();
    }
    g<<t-1;
    g.close();
    return 0;
}
