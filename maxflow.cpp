https://cses.fi/problemset/task/1694
#include <iostream>
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
 
using namespace std;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define mod 1000000007
#define lsb (i & -i)
#define pii pair<int,int> 
#define ll long long
///__builtin_popcount(x)
 
int n, m;
ll flow;
vector<vector<int> > G;
vector<vector<ll>> C;
vector<int> root;
int x,y;
ll c;
 
bool bfs(int k){
 
    queue<int> q;
    
    q.push(k);
 
    fill(root.begin(), root.end(), 0);
 
    while(!q.empty()){
 
        int x = q.front(); 
        q.pop();
 
        for(auto  i : G[x])
            if(!root[i] && C[x][i] > 0){
 
                root[i] = x;
 
                q.push(i);
 
                if (i == n)
                    return true;
            }
    }
 
    return false;
}
int main(){
 
    cin >> n >> m;
 
    G.resize(1LL * n + 1);
    root.resize(1LL * n + 1);
    C.resize(1LL * n + 1);
 
    for(int i = 1; i <= n; ++i)
        C[i].resize(1LL * n + 1);
 
    for(int i = 1 ; i <= m ; ++i){
        cin >> x >> y >> c;
        G[x].push_back(y);
        G[y].push_back(x);
 
        C[x][y] += c;
    }
 
    ll cmin = 0;
    int i;
 
    while(bfs(1)){
        
        cmin = MAX, i = n;
 
        while(i != 1){
            if(C[root[i]][i] < cmin)
                cmin = C[root[i]][i];
 
            i = root[i];
        }
 
        flow += 1ll * cmin;
 
        i = n;
 
        while (i != 1){
            C[root[i]][i] -= cmin;
            C[i][root[i]] += cmin;
            i = root[i];
        }
    }
    cout << flow;
    
    return 0;
}
