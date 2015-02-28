#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <ctime>
#define x first
#define y second
using namespace std;

int n,m;
bitset<1005> fol;
bitset<500000> fe;
pair<int,int> e[500000];

#include <cstdio>
//<parsing>
FILE* fin=fopen("autostrazi2.in","r");
const unsigned maxb=3000192;
char buf[maxb];
unsigned ptr=maxb;

inline unsigned getInt(){
    unsigned nr=0;
    while(buf[ptr]<'0'|'9'<buf[ptr])
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    while('0'<=buf[ptr]&&buf[ptr]<='9'){
        nr=nr*10+buf[ptr]-'0';
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    return nr;
}
//</parsing>

int main()
{
    ofstream g("autostrazi2.out");
    n=getInt(),m=getInt();
    for(int i=0; i<m; ++i) e[i].x=getInt(),e[i].y=getInt();
    //sort(e,e+m);
    srand(time(0));
    
    for(;;) {
        random_shuffle(e,e+m);
        int ok=1;
        fol&=0;
        fe&=0;
        for(int i=0; i<m; ++i) if(!fol[e[i].x] && !fol[e[i].y]) {
            fol[e[i].x]=1, fol[e[i].y]=1;
            fe[i]=1;
        }
        for(int i=1; i<=n; ++i) if(!fol[i]) {
            ok=0;
            break;
        }
        if(!ok) continue;
        for(int i=0; i<m; ++i) if(fe[i]) g<<e[i].x<<' '<<e[i].y<<'\n';
        break;
    }
    return 0;
}
