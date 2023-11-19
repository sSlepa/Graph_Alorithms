#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <stack>
#include <unordered_map>
#include <map>
#include <cmath>
#include <chrono>
#include <set>
#include <iomanip>
#include <list>

using namespace std;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define MOD 1000000007
#define MODC 984162946217979097
#define lsb(i) (i & -i)
#define pii pair<int,int>
#define tup tuple<int,int,int>
#define ll long long
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

int n,m,x,y;
queue<int > q;
vector<int> G[100005];
int GradInt[100005];
int LPT[100005];
int t[100005];

void afis(int nod){
    
    if(t[nod] == 0)
        cout << nod << ' ';

    else{
        afis(t[nod]);
        cout << nod << ' ';
    }

}

int main(){

    fastio
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i){

        cin >> x >> y;
        G[x].push_back(y);
        GradInt[y]++;

    }
    for(int i = 1 ; i <= n ; ++i){
        if(GradInt[i] == 0)
            q.push(i);
        
        LPT[i] = 1;
    }

    while(!q.empty()){

        int x = q.front();
        q.pop();
        for(auto i : G[x]){
            GradInt[i]--;
            LPT[i] = max(LPT[i],1 + LPT[x]);
            if(GradInt[i] == 0){
                q.push(i);
                t[i] = x;
            }
        }

    }
    int maxi = 0;
    int nod = 0;
    for(int i = 1 ; i <= n ; ++i)
        if(LPT[i] > maxi){
            maxi = LPT[i];
            nod = i;
        }

    cout << maxi << '\n';
    afis(nod);

    
    return 0;
}
