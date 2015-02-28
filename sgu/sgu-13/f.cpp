#include <iostream>
#include <deque>
#include <cstring>
#include <vector>
using namespace std;

    int n,m,k,nr_n,i;
    char T[10];
    char Name[200000][10];
    char Start[40005][10];
    char c;
    int poz,stiva;
    deque <int> Deq;
    vector<int> Rez_fin;

    void add ( int val )
    {
        if ( !poz )
        {
            // normal
            Deq.push_back(val);
            stiva++;
            if ( stiva > k )
            {
                Rez_fin.push_back ( Deq.front() );
                Deq.pop_front();

            }
        }
        else{
            // invers
            Deq.push_front(val);
            stiva++;
            if ( stiva > k )
            {
                Rez_fin.push_back ( Deq.back() );
                Deq.pop_back();

            }
        }
    }

    void scoate ( )
    {
        if ( !poz )
        {
            while ( !Deq.empty() )
            {
                Rez_fin.push_back( Deq.front() );
                Deq.pop_front();
            }
        }
        else{
            while ( !Deq.empty() )
            {
                Rez_fin.push_back( Deq.back() );
                Deq.pop_back();
            }
        }
    }

int main()
{
    cin>>n>>m>>k;
    for ( i=n; i>=1; i-- )
        cin>>Start[i];
    for ( i=1; i<=n; i++ )
    {
        strcpy(T,Start[i]);
        strcpy(Name[ ++nr_n ],T);
        add ( nr_n );
    }
    for ( i=1; i<=m; i++ )
    {
        cin>>c;
        if ( c== 'A' )
        {
            cin>>c>>c>>c;
            cin>>T;
            T[ strlen(T)-1 ]='\0';
            strcpy(Name[ ++nr_n ],T);
            add ( nr_n );
        }
        else{
            cin>>c>>c>>c>>c>>c;
            poz^=1;
        }
    }
    scoate();
    for ( i=Rez_fin.size()-1; i>=0; i-- )
        cout<<Name[ Rez_fin[i] ]<<'\n';
    return 0;
}
