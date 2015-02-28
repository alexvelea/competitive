#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

    char Text[100005];

int main(){
    
    freopen ("compress.in","r",stdin);
    freopen ("compress.out","w",stdout);

    //scanf ("%s", &Text);
    cin.read(Text,100005);
    int n=strlen(Text);
    for ( int i=0; i<n; ){
        int j=i;
        if ( Text[i]=='\n' )
            return 0;
        while ( (i<n) && ( Text[i]==Text[j] ) )
            i++;
        printf("%c%d",Text[j],i-j);
    }
    return 0;
}
