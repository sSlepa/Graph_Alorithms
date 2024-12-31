#include<iostream>
#include<vector>
#include<bitset>
using namespace std;



const int NMAX = 1e5 + 1;

bitset<NMAX> viz;

bool pairup(int nod,vector<int> &st,vector<int> &dr,vector<int> vecini[])
{
    if(viz[nod])
        return 0;

    viz[nod] = 1;
    for(auto it : vecini[nod])///incerc sa gasesc un nod liber
        {
            if(dr[it] == 0)
                {
                    st[nod] = it;
                    dr[it] = nod;
                    return 1;
                }
        }

    for(auto it : vecini[nod])///incerc sa gasesc un lant alternant
        {
            if(pairup(dr[it],st,dr,vecini))
                {
                    st[nod] = it;
                    dr[it] = nod;
                    return 1;
                }
        }

    return 0;
}

void solve()
{
    int n,m,a,b; cin >> n >> m;
    vector<int> st(n + 1,0),dr(m + 1,0);
    vector<int> vecini[n + 1];
    for(int i = 1; i <= n ; i++)
        {
            cin >> a >> b;
            vecini[i].push_back(a);
            vecini[i].push_back(b);
        }

    for(;;)
        {
            for(int i = 1; i <= n ; i++) viz[i] = 0; bool semafor = false;
            for(int i = 1; i <= n ; i++)
                {
                    if(!st[i]) semafor |= pairup(i,st,dr,vecini);
                }

            if(!semafor) break;
        }

    bool ok = 1;
    for(int i = 1; i <= n ; i++)
        {
            if(!st[i]) ok = false;
        }

    if(ok) cout << "DA\n";
    else cout << "NU\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    
    return 0;///superpeace
}
