//// https://www.infoarena.ro/problema/joc4
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

ifstream in ("joc4.in");
ofstream out ("joc4.out");

const int max_size = 501, INF = 1e9 + 1;

int cap[max_size][max_size], t[max_size], n, s, d;
vector <int> mc[max_size];
bitset <max_size> viz;

bool bfs (){
    queue <int> q;
    for (int i = 1; i <= 2 * n; i++){
        viz[i] = 0;
        t[i] = 0;
    }
    viz[s] = 1;
    q.push(s);
    while (!q.empty()){
        int nod = q.front();
        q.pop();
        for (auto f : mc[nod]){
            if(!viz[f] && cap[nod][f] > 0){
                t[f] = nod;
                viz[f] = 1;
                if (f == d){
                    return true;
                }
                q.push(f);
            }
        }
    }
    return false;
}

int main(){
    
    int q;
    in >> n >> q >> s >> d;
    for (int i = 1; i <= n; i++){
        mc[i].push_back(i + n);
        mc[i + n].push_back(i);
        cap[i + n][i]++; /// muchia de intoarcere
    }
    cap[s + n][s] = INF;
    cap[d + n][d] = INF;
    while (q--){
        int x, y;
        in >> x >> y;
        cap[x][y + n]++;
        cap[y][x + n]++;
        mc[x].push_back(y + n);
        mc[y].push_back(x + n);
        mc[x + n].push_back(y);
        mc[y + n].push_back(x);
    }
    int flux = 0;
    while (bfs()){
        for (auto f : mc[d]){
            if (cap[f][d] <= 0 || !viz[f])
                continue;

            t[d] = f;
            int mn = INF, nod = d;
            while (nod != s){
                mn = min(mn, cap[t[nod]][nod]);
                nod = t[nod];
            }
            if (mn == 0)
                continue;
            nod = d;
            while (nod != s){

                cap[t[nod]][nod] -= mn;
                cap[nod][t[nod]] += mn;
                nod = t[nod];
            }
            flux += mn;
        }
    }
    out << flux;
    in.close();
    out.close();

    return 0;
}
