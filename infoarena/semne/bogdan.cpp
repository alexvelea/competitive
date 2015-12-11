#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

FILE*f=fopen("semne.in","r");
FILE*h=fopen("semne.out","w");

int semn[50001];

long long v[50001];

int m[50001],p[50001];

int main(){
    int n;
    long long sum,s=0;
    fscanf(f,"%d%lld",&n,&sum);
    for ( int i=1;i<=n;++i ){
        fscanf(f,"%d",&v[i]);
        if ( s<sum ){
            s+=v[i];
            semn[i]=1;
            p[++p[0]]=i;
        }
        else {
            s-=v[i];
            semn[i]=-1;
            m[++m[0]]=i;
        }
        v[i]*=2;
    }
    int x;
    srand(time(NULL));
    while ( s!=sum ){
        if ( s>sum ){
            x=rand()%p[0]+1;
            s-=v[p[x]];
            semn[p[x]]=-1;
            m[++m[0]]=p[x];
            p[x]=p[p[0]];
            --p[0];
            continue;
        }
        x=rand()%m[0]+1;
        s+=v[m[x]];
        semn[m[x]]=1;
        p[++p[0]]=m[x];
        m[x]=m[m[0]];
        --m[0];
    }
    for ( int i=1;i<=n;++i ){
        if ( semn[i]==1 )
            fprintf(h,"+");
        else fprintf(h,"-");
    }
    return 0;
}
