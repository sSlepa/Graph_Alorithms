///https://kilonova.ro/problems/4
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <map>
#include <set>
#include <deque>
#include <algorithm>


constexpr auto Inf = std::numeric_limits <int64_t>::max ();
using Ip = std::pair <int, int>;
using VIp = std::vector <Ip>;
using VVIp = std::vector <VIp>;
using Vi = std::vector <int>;
using VVi = std::vector <Vi>;
using Vi64 = std::vector <int64_t>;
using STi = std::set <int>;
using Hsi64i = std::map <int64_t, int>;
using DQi = std::deque <int>;
using Vb = std::vector <bool>;


int n, m, u, v, w;
VVIp Graph, TGraph;
VVi NGraph;
Vi64 DistanceX, DistanceY;
Vi Tag, Disc, Low, Parent;
DQi DQ;
Hsi64i Hash;
STi Store, Store_AP;
Vb Seen;

 
inline void DEsopoPape (const int& src, Vi64& Distance, const VVIp& Graph) {
    Tag.assign (n + 1, 2);
    DQ.push_back (src), Distance[src] = 0LL;

    while (!DQ.empty ()) {
        int u = DQ.front ();
        DQ.pop_front (), Tag[u] = 0;
        
        for (const auto& e: Graph[u])
            if (Distance[e.first] > Distance[u] + e.second) {
            Distance[e.first] = Distance[u] + e.second;
            if (Tag[e.first] == 2)
                Tag[e.first] = 1, DQ.push_back (e.first);
            else if (!Tag[e.first])
                Tag[e.first] = 1, DQ.push_front (e.first);
        }
    }
}

inline void DFS (const int& root, const int& depth) {
    Disc[root] = Low[root] = depth;
    Seen[root] = true;
    int children = 0;

    for (const auto& v : NGraph[root]) {
        if (Seen[v])
            Low[root] = std::min (Low[root], Disc[v]);
        else {
            ++ children;
            Parent[v] = root;
            DFS (v, depth + 1);
            Low[root] = std::min (Low[root], Low[v]);
            if ((!Parent[root] && children > 1) || (Parent[root] && Low[v] >= Disc[root]))
                Store_AP.insert (root);
        }
    }

}

inline void Cut_Vertices () {
    for (int v = 1; v <= n; ++ v)
        if (!Seen[v]) DFS (v, 1);

    Store.insert (1), Store.insert (n);
    for (const auto& v : Store_AP)
        Store.insert (v);
}

 
int main () {
    std::cin >> n >> m;
    Graph.resize (n + 1), TGraph.resize (n + 1), NGraph.resize (n + 1);
    DistanceX.assign (n + 1, Inf), DistanceY.assign (n + 1, Inf);
    Disc.resize (n + 1), Low.resize (n + 1), Parent.resize (n + 1), Seen.resize (n + 1);
    
    for (int i = 1; i <= m; ++ i)
        std::cin >> u >> v >> w,
        Graph[u].emplace_back (std::make_pair (v, w)),
        TGraph[v].emplace_back (std::make_pair (u, w));

    DEsopoPape (1, DistanceX, Graph), DEsopoPape (n, DistanceY, TGraph);
    for (int u = 1; u <= n; ++ u)
        for (const auto& e: Graph[u])
            if (DistanceX[n] == DistanceX[u] + e.second + DistanceY[e.first])
                NGraph[u].emplace_back (e.first), NGraph[e.first].emplace_back (u);

    Cut_Vertices ();
    std::cout << Store.size () << "\n";
    for (const auto& u: Store)
        std::cout << u << " ";

    return 0;
}
