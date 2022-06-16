// A C++ program to find maximal
// Bipartite matching.
#include <iostream>
#include <cstring>
#include <vector>
#include "FordFulkerson.hpp"
using namespace std;

int maxBPM(vector<vector<bool>> bpGraph, int n, int m)
{
    int V = n + m + 2;
    int s = n + m;
    int t = n + m + 1;
    vector<pair<int, int>> adj[V];
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < m; v++)
        {
            if (bpGraph[u][v])
            {
                adj[u].push_back({n + v, 1});
            }
        }
    }
    for (int u = 0; u < n; u++)
    {
        adj[s].push_back({u, 1});
    }
    for (int u = 0; u < m; u++)
    {
        adj[n + u].push_back({t, 1});
    }
    return fordFulkerson(adj, V, s, t);
}

// Driver Code
int main()
{
    // Let us create a bpGraph
    // shown in the above example
    int n = 6, m = 6;
    vector<vector<bool>> bpGraph = {{0, 1, 1, 0, 0, 0},
                                    {1, 0, 0, 1, 0, 0},
                                    {0, 0, 1, 0, 0, 0},
                                    {0, 0, 1, 1, 0, 0},
                                    {0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 1}};

    cout << "Maximum number of applicants that can get job is " << maxBPM(bpGraph, n, m);

    return 0;
}
