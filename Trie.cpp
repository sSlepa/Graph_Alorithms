#include <bits/stdc++.h>
using namespace std;

ifstream fin("trie.in");
ofstream fout("trie.out");

class Trie {
    int cnt = 0;
    int lvs = 0;
    Trie *next[26] = {};

public:
    void insert(const string& str, int pos = 0) {
        lvs++;
        if (pos == int(str.size()))
            cnt++;
        else {
            if (!next[str[pos] - 'a'])
                next[str[pos] - 'a'] = new Trie;
            next[str[pos] - 'a']->insert(str, pos + 1);
        }
    }

    void erase(const string& str, int pos = 0) {
        lvs--;
        if (pos == int(str.size()))
            cnt--;
        else {
            next[str[pos] - 'a']->erase(str, pos + 1);
            if (!next[str[pos] - 'a']->lvs) {
                delete next[str[pos] - 'a'];
                next[str[pos] - 'a'] = nullptr;
            }
        }
    }

    int count(const string& str, int pos = 0) {
        if (pos == int(str.size()))
            return cnt;
        if (!next[str[pos] - 'a'])
            return 0;
        return next[str[pos] - 'a']->count(str, pos + 1);
    }

    int lcp(const string& str, int pos = 0) {
        if (pos == int(str.size()))
            return 0;
        if (!next[str[pos] - 'a'])
            return 0;
        return 1 + next[str[pos] - 'a']->lcp(str, pos + 1);
    }
};

int main() {
    Trie trie;
    int type; string str;
    while (fin >> type >> str)
        if (!type)
            trie.insert(str);
        else if (type == 1)
            trie.erase(str);
        else if (type == 2)
            fout << trie.count(str) << '\n';
        else
            fout << trie.lcp(str) << '\n';
    return 0;
}
