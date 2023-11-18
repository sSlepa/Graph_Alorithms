#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
 
#define NMAX 50001
#define INF 0x3f3f3f3f
 
#define pb push_back
#define mp make_pair
#define nod first
#define cost second
 
using namespace std;
 
ifstream in("bellmanford.in");
ofstream out("bellmanford.out");
 
vector< pair< int, int > > G[NMAX];
vector< pair< int, int > >::iterator Vecin;
queue< int > Q;
int N, M, i, x, y, c, D[NMAX], It, ItNod[NMAX], Nod;
bool USED[NMAX];
 
int main()
{
    in >> N >> M;
    for( ; M--; )
    {
        in >> x >> y >> c;
        G[x].pb( mp( y, c ) );
    }
 
    memset( USED, false, sizeof(USED) ); //initial nu avem noduri in coada
    memset( D, INF, sizeof(D) ); //toate distantele sunt infinit
    D[1] = 0; //mai putin cea pana la sursa
    memset( ItNod, 0, sizeof(ItNod) ); //nu s-a trecut niciodata prin niciun nod
    Q.push( 1 ); //introducem nodul 1 in coada
    USED[1] = true;
 
    while( !Q.empty() )
    {
        Nod = Q.front();
        Q.pop();
        USED[Nod] = false; // scoatem nodul din coada
 
        for( Vecin = G[Nod].begin(); Vecin != G[Nod].end(); Vecin++ ) // iteram prin vecinii nodului
            if( D[(*Vecin).nod] > D[Nod] + (*Vecin).cost ) // incercand sa minimizam distanta pana la acestia
            {
                D[(*Vecin).nod] = D[Nod] + (*Vecin).cost;
 
                if( !USED[(*Vecin).nod] ) // daca nodul nu se afla in coada
                {
                    Q.push( (*Vecin).nod ); // il introducem
                    USED[(*Vecin).nod] = true;
                    if( ++ItNod[(*Vecin).nod] > N ) // dca s-a trecut de mai mult de N ori prin el
                    {
                        out << "Ciclu negativ!\n"; // inseamna ca in graf exista un ciclu negativ
                        return 0;
                    }
                }
            }
    }
 
    for( i = 2; i <= N; i++ )
        out << D[i] << ' '; // distantele de la nodul 1( sursa ) pana la celelalte noduri
 
    return 0;
}
