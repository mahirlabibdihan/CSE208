#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int64_t bfs(vector<int> adj[], int n, vector<vector<int64_t>> capacity, int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    queue<pair<int, int64_t>> q;
    q.push({s, LLONG_MAX});
    while (!q.empty())
    {
        auto [u, flow] = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (v != s && parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;
                int64_t new_flow = min(flow, capacity[u][v]);
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

void dfs(vector<int> adj[], vector<vector<int64_t>> capacity, int u, vector<bool> &reachable)
{
    reachable[u] = true;
    for (int v : adj[u])
    {
        if (!reachable[v] && capacity[u][v] > 0)
        {
            dfs(adj, capacity, v, reachable);
        }
    }
}

int64_t fordFulkerson(vector<pair<int, int64_t>> adj[], int n, int s, int t, vector<bool> &reachable)
{
    vector<vector<int64_t>> capacity(n, vector<int64_t>(n, 0));
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
    int64_t flow = 0;
    while (true)
    {
        vector<int> parent(n);
        int64_t new_flow = bfs(new_adj, n, capacity, s, t, parent); // O(V+E)
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
    fill(reachable.begin(), reachable.end(), false);
    dfs(new_adj, capacity, s, reachable);
    return flow;
}
// O(V)
bool isEdge(vector<pair<int, int64_t>> adj[], int u, int v)
{
    for (auto [i, j] : adj[u])
    {
        if (i == v)
        {
            return true;
        }
    }
    return false;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int extra = 0;
    vector<pair<int, int64_t>> adj[n + m];
    // O(VE)
    for (int i = 0; i < m; i++)
    {
        int64_t u, v, w = 1;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({n + extra, w});
        adj[n + extra].push_back({u, w});
        extra++;
    }
    vector<bool> reachable(n + extra);
    fordFulkerson(adj, n + extra, 0, n - 1, reachable);
    int count = 0;
    for (int u = 0; u < n; u++)
    {
        if (reachable[u])
        {
            for (auto [v, w] : adj[u])
            {
                if (!reachable[v])
                {
                    count++;
                }
            }
        }
    }
    cout << count << endl;
    for (int u = 0; u < n; u++)
    {
        // cout << u << endl;
        if (reachable[u])
        {
            // cout << u << endl;
            for (auto [v, w] : adj[u])
            {
                // cout << v << endl;
                if (!reachable[v])
                {
                    if (v < n)
                    {
                        cout << u + 1 << " " << v + 1 << endl;
                    }
                    else
                    {
                        cout << u + 1 << " " << adj[v].front().first + 1 << endl;
                    }
                }
            }
        }
    }
}