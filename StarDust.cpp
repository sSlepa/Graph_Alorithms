/*
 *
 * @author Popa Sebastian
 * Single Shortest Path algorithm on DG using SPFA algorithm
 * Complexity: O(V*S + V*E)
 *
 *
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include <limits>
#include <functional>
#include <cctype>

#define INF std::numeric_limits<int64_t>::max()

namespace FastRead
{
    const int Dim(1 << 16);
    char buff[Dim];
    int pos, len;
    std::FILE *file = std::fopen("stardust.in", "r");
    inline char nc()
    {
        if (pos == len)
        {
            pos = 0;
            len = std::fread(buff, 1, Dim, file);
            if (!len)
                return EOF;
        }
        return buff[pos++];
    }
    template <class T>
    inline void Read(T &x)
    {
        char ch;
        int sgn(1);
        while (!std::isdigit(ch = nc()))
            if (ch == '-')
                sgn = -1;
        x = ch - '0';
        while (std::isdigit(ch = nc()))
            x = x * 10 + (ch - '0');
        x *= sgn;
    }
} // namespace FastRead
using namespace FastRead;
std::ofstream fout("stardust.out");

class TreeNode
{
private:
    int id;
    TreeNode *parent;
    std::list<TreeNode *> children;

public:
    TreeNode(int _id) : id(_id), parent(nullptr) {}
    TreeNode(int _id, TreeNode *_parent) : id(_id), parent(_parent) {}
    void addChildren(TreeNode *node)
    {
        children.push_back(node);
    }
    int getId()
    {
        return id;
    }
    TreeNode *getParent()
    {
        return parent;
    }
    std::list<TreeNode *> getChildren()
    {
        return children;
    }
};

int V, E, S, x, y, u, v, w, cnt;
std::queue<int> Q;
std::vector<std::vector<std::pair<int, int>>> Graph;
std::vector<std::vector<std::vector<int>>> Trees;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> PQ;
std::vector<bool> Seen, InQueue;
std::vector<int> QueueOcc, Store;
std::vector<int64_t> Distance1;
inline std::string encode(TreeNode *node)
{
    if (!node)
        return "";
    std::vector<std::string> labels;
    for (TreeNode *child : node->getChildren())
        labels.push_back(encode(child));
    std::sort(labels.begin(), labels.end());
    std::string s("(");
    for (auto label : labels)
        s += label;
    s += ")";
    return s;
}
inline TreeNode *buildTree(std::vector<std::vector<int>> graph, TreeNode *node)
{
    for (auto neighbor : graph[node->getId()])
    {
        if (node->getParent())
            if (neighbor == node->getParent()->getId())
                continue;

        TreeNode *child = new TreeNode(neighbor, node);
        node->addChildren(child);

        buildTree(graph, child);
    }
    return node;
}
inline TreeNode *rootTree(std::vector<std::vector<int>> graph, int rootId)
{
    TreeNode *root = new TreeNode(rootId);
    return buildTree(graph, root);
}
inline std::list<int> findTreeCenters(std::vector<std::vector<int>> Tree)
{
    int n = Tree.size() - 1;
    std::vector<int> Degree(n + 1);
    std::list<int> Leaves;
    for (int i = 1; i <= n; ++i)
    {
        std::vector<int> edges = Tree[i];
        Degree[i] = edges.size();
        if (Degree[i] <= 1)
            Leaves.push_back(i), Degree[i] = 0;
    }
    int processedLeaves = Leaves.size();
    while (processedLeaves < n)
    {
        std::list<int> newLeaves;
        for (auto node : Leaves)
        {
            for (auto neighbor : Tree[node])
                if (--Degree[neighbor] == 1)
                    newLeaves.push_back(neighbor);
            Degree[node] = 0;
        }
        processedLeaves += newLeaves.size();
        Leaves = newLeaves;
    }
    return Leaves;
}
inline bool treesAreIsomorphic(std::vector<std::vector<int>> Tree1, std::vector<std::vector<int>> Tree2)
{
    std::list<int> centers1 = findTreeCenters(Tree1);
    std::list<int> centers2 = findTreeCenters(Tree2);

    TreeNode *rootedTree1 = rootTree(Tree1, centers1.front());
    std::string tree1Encoding = encode(rootedTree1);

    for (auto center : centers2)
    {
        TreeNode *rootedTree2 = rootTree(Tree2, center);
        std::string tree2Encoding = encode(rootedTree2);

        if (tree1Encoding == tree2Encoding)
            return true;
    }
    return false;
}
inline bool Bellman_Ford()
{
    bool negative_cycle = false;
    PQ.push(std::make_pair(0, x)), Distance1[x] = 0, InQueue[x] = true, ++QueueOcc[x];
    while (!PQ.empty() && !negative_cycle)
    {
        int curr = PQ.top().second;
        PQ.pop();
        InQueue[curr] = false;
        for (auto it : Graph[curr])
            if (Distance1[curr] != INF)
                if (Seen[it.first] && Distance1[it.first] > Distance1[curr] + it.second)
                {
                    Distance1[it.first] = Distance1[curr] + it.second;
                    if (!InQueue[it.first])
                    {
                        if (QueueOcc[it.first] > cnt)
                            negative_cycle = true;
                        else
                            PQ.push(std::make_pair(Distance1[it.first], it.first)),
                                InQueue[it.first] = true, ++QueueOcc[it.first];
                    }
                }
    }
    return negative_cycle;
}
int main()
{
    Read(V), Read(E), Read(x), Read(y), Read(S);
    Graph.resize(V + 1);
    Trees.resize(V + 1);
    Seen.assign(V + 1, false), InQueue.assign(V + 1, false);
    Distance1.assign(V + 1, INF), QueueOcc.assign(V + 1, 0);
    for (int i = 1; i <= E; ++i)
        Read(u), Read(v), Read(w),
            Graph[u].emplace_back(std::make_pair(v, w));
    for (int i = 1; i <= V; ++i)
    {
        Trees[i].resize(S + 1);
        for (int j = 1; j < S; ++j)
            Read(u), Read(v),
                Trees[i][u].emplace_back(v),
                Trees[i][v].emplace_back(u);
    }
    for (int i = 1; i <= V; ++i)
    {
        Seen[i] = treesAreIsomorphic(Trees[x], Trees[i]);
        if (Seen[i])
            ++cnt;
    }
    if (!Bellman_Ford())
        fout << Distance1[y];
    else
        fout << "Black hole detected!";

    fout.close();
    return 0;
}
