/// Drumuri2 Pbinfo 100 puncte - Solutie cu ajutorul lui Crispi <3
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <stack>

using namespace std;
#define Inf 0x3f3f3f3f

ifstream cin("drumuri.in");
ofstream cout("drumuri.out");

int n,m;
vector<int> G[150005];
vector<int> DaG[150005];
int v[150005],low[150005],val,CompConex;
stack<int> st;
bool InQueue[150005],popular[150005];
int rez[150005];
int Comp[150005];
int Grad[150005];
int Cost[150005];
int x,y;

void dfs(int node){

    v[node] = val; low[node] = val; val++;
    st.push(node); 
    InQueue[node] = true;
    for(auto i : G[node]){
        if(v[i] == -1) 
            dfs(i);
        if(InQueue[i]) 
            low[node] = min(low[node], low[i]);
    }
 
    if(v[node] == low[node]){
        CompConex++;
        int current;
        while(current != node){
            current = st.top(); 
            st.pop(); 
            InQueue[current] = false;
            Comp[current] = CompConex;
        }
    }
}

void detmax(int nod){

    for(auto i : DaG[nod]){
        if(Cost[i] == -1) 
            detmax(i);

        Cost[nod] = max(Cost[nod],Cost[i] + 1);
    }
    if(Cost[nod] == -1) 
        Cost[nod] = 0;
}

int main(){

    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i){
        cin >> x >> y;
        G[x].push_back(y);
    }
    for(int i = 1 ; i <= n ; ++i)
        v[i] = -1;
    
    for(int i = 1 ; i <= n ; ++i){
        if(v[i] == -1)
            dfs(i);
    }
    for(int i = 1 ; i <= n ; ++i)
        for(auto j : G[i]){
            if(Comp[i] != Comp[j]){
                DaG[Comp[i]].push_back(Comp[j]);
                Grad[Comp[j]]++;
        }
    }
    /*
    for(int i = 1 ; i <= n ; ++i)
        cout << Comp[i] << ' ';
    */
    set<int> s;
    for(int i = 1 ; i <= CompConex ; ++i){
        if(Grad[i] == 0)
            s.insert(i);

        Cost[i] = -1;

    }
    while(!s.empty()){
        if(s.size() == 1)
            popular[*s.begin()] = true;

        int MaxCurent = 0;
        for(auto i : s){
            if(Cost[i] == -1)
                detmax(i);

            MaxCurent = max(MaxCurent,Cost[i]);

        }
        vector<set<int>::iterator> pos;
        for(set<int>::iterator it = s.begin(); it != s.end(); ++it){
            int i = *it;
            if(Cost[i] == MaxCurent){
                pos.push_back(it);
                for(auto j : DaG[i]){
                    Grad[j]--;
                    if(Grad[j] == 0) 
                        s.insert(j);
                }
            }
        }
        for(auto it : pos) 
            s.erase(it);

    }
    int cnt = 0;
    for(int i = 1 ; i <= n ; ++i){
        rez[i] = popular[Comp[i]];
        cnt += rez[i];
    }

    cout << cnt << "\n";
    for(int i = 1 ; i <= n ; ++i) 
        if(rez[i]) 
            cout << i << " ";

    
    return 0;
}
