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
#include <sstream>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_set>
#include <random>
#include <time.h>
#include <Windows.h>

using namespace std;
using namespace chrono;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define MOD 1000000007
#define MODC 984162946217979097
#define lsb(i) (i & -i)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define tup tuple<int,int,int>
#define ll long long
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

char a[1005][1005];
int x,y,z;
int dist[1005][1005];
int reweight[1005][1005];
int t[1005][1005];
int n;

static inline int64_t GetTicks() {

    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks)){
        // Handle error (you can throw an exception or handle it differently)
        // For example, using WinRT's throw_last_error():
        // winrt::throw_last_error();
    }
    return ticks.QuadPart;
}

bool inmat(int i,int j){

    return i >= 0 && i < n && j >= 0 && j < n;

}

int potential(int x,int y){

    return abs(n - x) + abs(n - y);

}

void reconstruct_road(int i,int j){

    if(i == 0 && j == 0){
        cout << 0 << ' ' << 0 << '\n';
        return;
    }
    reconstruct_road(i - dx[t[i][j]],j - dy[t[i][j]]);
    cout << i << ' ' << j << '\n';

}

void a_star(){

    priority_queue<tup,vector<tup>,greater<tup>> q;
    dist[0][0] = 0;
    reweight[0][0] = potential(0,0);
    q.push(make_tuple(potential(0,0),0,0));
    while(!q.empty()){
        
        int x,y;
        x = get<1>(q.top());
        y = get<2>(q.top());
        q.pop();
        for(int d = 0 ; d < 4 ; ++d){
            int ii = x + dx[d];
            int jj = y + dy[d];
            if(inmat(ii,jj) && a[ii][jj] != '#' && dist[ii][jj] > dist[x][y] + 1){
                dist[ii][jj] = dist[x][y] + 1;
                t[ii][jj] = d;
                reweight[ii][jj] = dist[x][y] + 1 + potential(ii,jj);
                q.push(make_tuple(dist[ii][jj],ii,jj));
            }
        }
    }
    cout << dist[n - 1][n - 1] << '\n';
    reconstruct_road(n - 1,n - 1);
}

int main(){

    fastio;

    int64_t start = GetTicks();

    cin >> n;

    for(int i = 0 ; i < n ; ++i)
        cin >> a[i];

    for(int i = 0 ; i < n ; ++i)
        for(int j = 0 ; j < n ; ++j)
            dist[i][j] = Inf;

    a_star();

    int64_t end = GetTicks();

    cout << "\n";

    cout << "CPU Clocks start : " << start << '\n';
    cout << "CPU Clocks final : " << end << '\n';
    cout << "Difference : " << end - start << '\n';

    double elapsedTimeSeconds = (double)(end - start);

    cout << "Elapsed time: " << fixed << setprecision(3) << elapsedTimeSeconds / 1e4 << " miliseconds";




    return 0;
}
