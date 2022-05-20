#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Graph
{
  vector<vector<int>> adj; // Graph represented as adjacency list
  int n;                   // number of nodes in graph

  vector<int> time_in, time_out, color, low;
  vector<bool> visited;

  Graph(vector<vector<int>> adjacent, int nodes)
  {
    adj = adjacent;
    n = nodes;

    time_in = vector<int>(n);
    time_out = vector<int>(n);
    color = vector<int>(n);
    visited = vector<bool>(n);
    low = vector<int>(n);
  }

  // Implementation of DFS algorithms

  void dfs(int v)
  {
    static int dfs_timer = 0;
    visited[v] = true;
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
    {
      if (color[u] == 0)
      {
        dfs(u);
      }
    }
    color[v] = 2;
    time_out[v] = dfs_timer++;
  }

  // Identify Edge in the graph
  void identify_edge(int u, int v)
  {
    dfs(u);
    if (time_in[v] - time_in[u] == 1)
    {
      cout << "Tree Edge";
    }
    else if (time_in[v] < time_in[u] && color[v] == 1)
    {
      cout << "Back Edge";
    }
  }

  // Breadth First Search Algorithm.
  vector<int> bfs(int s)
  {
    queue<int> q;
    vector<bool> used(n);
    vector<int> d(n, -1), p(n);
    used[s] = true;
    p[s] = -1;
    d[s] = 0;

    while (!q.empty())
    {
      int v = q.front();
      q.pop();
      for (int u : adj[v])
      {
        if (!used[u])
        {
          used[u] = true;
          q.push(u);
          d[u] = d[v] + 1;
          p[u] = v;
        }
      }
    }

    return d;
  }

  // to perform recursion in the isCyclic function.
  bool isCyclicRec(int v, vector<bool> visited, vector<bool> recStack)
  {
    if (visited[v] == false)
    {
      visited[v] = true;
      recStack[v] = true;
      for (int i : adj[v])
      {
        if (!visited[i] && isCyclicRec(i, visited, recStack))
          return true;
        else if (recStack[i])
          return true;
      }
    }
    recStack[v] = false;
    return false;
  }

  // to find is there exist a cycle or not
  bool isCyclic()
  {
    vector<bool> visited(n, false), recStack(n, false);
    for (int i = 0; i < n; i++)
    {
      if (!visited[i] && isCyclicRec(i, visited, recStack))
        return true;
    }
    return false;
  }

  void modified_dfs(int v, int p, vector<pair<int, int>> &bridges)
  {
    static int dfs_timer = 0;
    visited[v] = true;
    time_in[v] = low[v] = dfs_timer++;
    for (int u : adj[v])
    {
      if (u == p)
        continue;
      if (visited[u])
      {
        low[v] = min(low[v], time_in[u]);
      }
      else
      {
        modified_dfs(u, v, bridges);
        low[v] = min(low[v], low[u]);
        if (low[u] > time_in[v])
          bridges.push_back({v, u});
      }
    }
  }

  // Find bridges in the graph and list them.
  void find_bridges()
  {
    vector<pair<int, int>> bridges;
    int timer = 0;
    for (int i = 0; i < n; i++)
    {
      if (visited[i])
      {
        modified_dfs(i, -1, bridges);
      }
    }

    for (pair<int, int> t : bridges)
    {
      cout << t.first << " " << t.second << endl;
      cout << t.second << " " << t.first << endl;
    }
  }

  void DFSUtil(int v, vector<bool> visited)
  {
    visited[v] = true;
    cout << v << "";
    for (int u : adj[v])
    {
      if (!visited[v])
      {
        DFSUtil(u, visited);
      }
    }
  }

  void find_connected_components()
  {
    vector<bool> visited(n, false);
    for (int v = 0; v < n; v++)
    {
      if (visited[v] == false)
      {
        DFSUtil(v, visited);
        cout << "\n";
      }
    }
  }
};