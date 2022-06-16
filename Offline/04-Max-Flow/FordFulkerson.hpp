#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

// O(V+E)
int bfs(vector<int> adj[], int n, vector<vector<int>> capacity, int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});
    while (!q.empty())
    {
        auto [u, flow] = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (v != s && parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t)
                {
                    return new_flow;
                }
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}
int fordFulkerson(vector<pair<int, int>> adj[], int n, int s, int t)
{
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    // O(E)
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w] : adj[u])
        {
            capacity[u][v] = w;
        }
    }

    vector<int> new_adj[n];
    // O(E)
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w] : adj[u])
        {
            new_adj[u].push_back(v);
            new_adj[v].push_back(u);
        }
    }
    int flow = 0;

    while (true)
    {
        vector<int> parent(n);
        int new_flow = bfs(new_adj, n, capacity, s, t, parent); // O(V+E)
        if (new_flow == 0)
        {
            break;
        }
        flow += new_flow;
        // O(V)
        for (int cur = t; cur != s; cur = parent[cur])
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
        }
    }
    return flow;
}