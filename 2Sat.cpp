
// https://www.infoarena.ro/problema/2sat
#include<bits/stdc++.h>
using namespace std;
ifstream f("2sat.in");
ofstream g("2sat.out"); 
int n, m;
Expand
trie.txt
2 KB
sSlepa — 11/05/2023 2:37 PM
 
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
Expand
cuvinte-73108.cpp
3 KB
sSlepa — 11/15/2023 11:51 PM
https://open.kattis.com/problems/capsules
sSlepa — 11/16/2023 5:39 PM
https://open.kattis.com/problems/pathtracing 
sSlepa — 11/16/2023 10:36 PM
#include <iostream>
#include <vector>

using namespace std;

int main() {
Expand
path.txt
2 KB
sSlepa — 11/16/2023 11:11 PM
capsules 
#include <bits/stdc++.h>

using namespace std;

struct group {
    vector<bool> used;
Expand
message.txt
3 KB
https://open.kattis.com/problems/neutralground
sSlepa — Yesterday at 6:41 PM
https://open.kattis.com/problems/distracted
sSlepa — Yesterday at 11:33 PM
https://open.kattis.com/problems/incognito
sSlepa — Today at 2:32 AM
https://open.kattis.com/problems/planets2
https://open.kattis.com/problems/landscape
https://open.kattis.com/problems/eulerian
https://open.kattis.com/problems/icouldhavewon
https://open.kattis.com/problems/repetitivesong
https://open.kattis.com/problems/esotericspells
https://open.kattis.com/problems/slikar
https://open.kattis.com/problems/firefly
https://open.kattis.com/problems/paintball
https://open.kattis.com/problems/dominos
https://open.kattis.com/problems/thinkingofanumber
https://open.kattis.com/problems/blackout
https://open.kattis.com/problems/4thought
https://open.kattis.com/problems/walrusweights
https://open.kattis.com/problems/keypad
https://open.kattis.com/problems/builddeps
https://open.kattis.com/problems/nizovi
https://open.kattis.com/problems/bigtruck
https://open.kattis.com/problems/gamerank
https://open.kattis.com/problems/applesack
https://open.kattis.com/problems?page=11&order=difficulty_data
sSlepa — Today at 1:15 PM
https://open.kattis.com/problems/collapse
sSlepa — Today at 4:25 PM
https://open.kattis.com/problems/longestpathinadag
https://open.kattis.com/problems/productdivisors
https://open.kattis.com/problems/primecount
https://open.kattis.com/problems/primality
﻿
// https://www.infoarena.ro/problema/2sat
#include<bits/stdc++.h>
using namespace std;
ifstream f("2sat.in");
ofstream g("2sat.out"); 
int n, m;
bool pus[200002], viz[200002];
int comp[200002];
vector<int>v[200002], tr[200002];
vector<int>ordine;
void dfs(int nod)
{
    viz[nod] = 1;
    for(int i = 0; i < v[nod].size(); ++i)
    {
        int vecin = v[nod][i];
        if(viz[vecin])
            continue;
        dfs(vecin);
    }
    ordine.push_back(nod);
}
int nr;
void dfs2(int nod)
{
    comp[nod] = nr;
    for(int i = 0; i < tr[nod].size(); ++i)
    {
        int vecin = tr[nod][i];
        if(comp[vecin])
            continue;
        dfs2(vecin);
    }
}
int main()
{
    f >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        int a, b;
        f >> a >> b;
        int nega = (a < 0);
        int negb = (b < 0);
        if(a < 0)
            a *= -1;
        if(b < 0)
            b *= -1;
        v[a * 2 + (!nega)].push_back(b * 2 + negb);
        v[b * 2 + (!negb)].push_back(a * 2 + nega);
        tr[b * 2 + negb].push_back(a * 2 + (!nega));
        tr[a * 2 + nega].push_back(b * 2 + (!negb));
    }
    for(int i = 2; i <= 2 * n + 1; ++i)
        if(!viz[i])
            dfs(i);
    reverse(ordine.begin(), ordine.end());
    for(int i = 0; i < ordine.size(); ++i)
    {
        int nod = ordine[i];
        if(!comp[nod])
            ++nr, dfs2(nod);
    }
    for(int i = 2; i <= 2 * n + 1; ++i)
        if(comp[i] == comp[i ^ 1])
        {
            g << -1;
            return 0;
        }
    for(int i = 1; i <= n; ++i)
        g << (comp[i * 2] > comp[i * 2 + 1]) << " ";
    return 0;
}
