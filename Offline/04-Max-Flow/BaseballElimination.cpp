// https://www.cs.princeton.edu/courses/archive/spr03/cos226/assignments/baseball.html
#include <iostream>
#include <vector>
#include <iomanip>
#include "FordFulkerson.hpp"
using namespace std;

void solve(vector<string> name, vector<int> w, vector<int> l, vector<int> r, vector<vector<int>> g, int n)
{
    int V = 2 + (n * (n - 1) / 2) + n;
    int s = V - 2;
    int t = V - 1;
    vector<pair<int, int>> adj[V];
    int max_flow = 0;
    int c = n;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++, c++)
        {
            adj[s].push_back({c, g[i][j]});
            adj[c].push_back({i, INT_MAX});
            adj[c].push_back({j, INT_MAX});
            max_flow += g[i][j];
        }
    }
    // All teams to sink
    for (int i = 0; i < n; i++)
    {
        adj[i].push_back({t, 0});
    }
    for (int x = 0; x < n; x++)
    {
        for (int i = 0; i < n; i++)
        {
            adj[i][0].second = w[x] + r[x] - w[i];
        }
        if (fordFulkerson(adj, V, s, t) < max_flow)
        {
            cout << name[x] << " is eliminated." << endl;
        }
    }
}

int main()
{
    freopen("mf.in", "r", stdin);
    int n;
    cin >> n;
    vector<string> name(n);
    vector<int> w(n), l(n), r(n);
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        cin >> name[i] >> w[i] >> l[i] >> r[i];
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
        }
    }
    solve(name, w, l, r, g, n);
}