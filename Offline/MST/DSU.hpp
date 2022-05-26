#ifndef __DSU__
#define __DSU__
class DSU
{
private:
    vector<int> parent;      // Node array
    int find(int curr) const // Find root
    {
        while (parent[curr] != -1)
            curr = parent[curr];
        return curr; // At root
    }

public:
    DSU(int n) : parent(n, -1) {} // Constructor
    void unite(int u, int v)      // Merge equivalences
    {
        int s1 = find(u);
        int s2 = find(v);
        if (s1 != s2)
        {
            parent[s2] = s1;
        }
    }
    bool differ(int u, int v) // True if not in same tree
    {
        return find(u) != find(v);
    }
};
#endif