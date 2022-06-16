// https://www.cs.princeton.edu/courses/archive/spr03/cos226/assignments/baseball.html
#include <iostream>
#include <vector>
#include <iomanip>
#include "FordFulkerson.hpp"
using namespace std;

void printNames(vector<string> names, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << names[i];
        if (i < n - 2)
        {
            cout << ", ";
        }
        else if (i < n - 1)
        {
            cout << " and ";
        }
    }
}

void printElimination(vector<string> name, vector<int> w, vector<int> r, vector<bool> reachable, int x, int n)
{
    int nWins = 0, nLeft = 0, nTeam = 0;
    vector<string> names;
    for (int i = 0; i < n; i++)
    {
        if (reachable[i])
        {
            nWins += w[i];
            nLeft += r[i];
            nTeam += 1;
            names.push_back(name[i]);
        }
    }
    cout << name[x] << " is eliminated." << endl;
    cout << "They can win at most " << w[x] << " + " << r[x] << " = " << w[x] + r[x] << " games." << endl;
    printNames(names, nTeam);
    cout << " have won a total of " << nWins << " games." << endl;
    cout << "They play each other " << nLeft << " times." << endl;
    cout << "So on average, each of the teams wins " << (nWins + nLeft) << "/" << nTeam << " = " << (1.0 * (nWins + nLeft) / nTeam) << " games." << endl
         << endl;
}
void check(vector<pair<int, int>> adj[], vector<string> name, vector<int> w, vector<int> r, int x, int n, int max_flow)
{
    int V = 2 + (n * (n - 1) / 2) + n;
    int s = V - 2;
    int t = V - 1;

    // Teams to sink
    for (int i = 0; i < n; i++)
    {
        adj[i].push_back({t, w[x] + r[x] - w[i]});
    }
    // Checking if it is possible to play all games and x not getting eliminated
    vector<bool> reachable(V);
    int flow = fordFulkerson(adj, V, s, t, reachable);
    if (flow < max_flow)
    {
        printElimination(name, w, r, reachable, x, n);
    }
}
void solve(vector<string> name, vector<int> w, vector<int> r, vector<vector<int>> g, int n)
{
    int V = 2 + (n * (n - 1) / 2) + n;
    int s = V - 2;
    int t = V - 1;
    vector<pair<int, int>> adj[V];
    int max_flow = 0;
    // Create graph
    for (int i = 0, c = n; i < n; i++)
    {
        for (int j = i + 1; j < n; j++, c++)
        {
            adj[s].push_back({c, g[i][j]});
            adj[c].push_back({i, INT_MAX});
            adj[c].push_back({j, INT_MAX});
            max_flow += g[i][j];
        }
    }
    for (int x = 0; x < n; x++)
    {
        check(adj, name, w, r, x, n, max_flow);
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
    solve(name, w, r, g, n);
}
/*
Test cases:
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0
5
New_York 75 59 28 0 3 8 7 3
Baltimore 71 63 28 3 0 2 7 4
Boston 69 66 27 8 2 0 0 0
Toronto 63 72 27 7 7 0 0 0
Detroit 49 86 27 3 4 0 0 0
*/