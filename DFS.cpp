#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;
const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];
void dfs(int node) {
 stack<int> s;
 s.push(node);
 while (!s.empty()) {
 int curr_node = s.top();
 s.pop();
 if (!visited[curr_node]) {
 visited[curr_node] = true;
 cout << curr_node << " ";
 // Vector to hold unvisited neighbors
 vector<int> unvisited_neighbors;
 // Iterate over neighbors to find unvisited ones
 #pragma omp parallel for
 for (int i = 0; i < graph[curr_node].size(); i++) {
 int adj_node = graph[curr_node][i];
 if (!visited[adj_node]) {
 // Store unvisited neighbors in the vector
 #pragma omp critical
 unvisited_neighbors.push_back(adj_node);
 }
 }
 // Push unvisited neighbors onto the stack
 for (int neighbor : unvisited_neighbors) {
 s.push(neighbor);
 }
 }
 }
}
int main() {
 int n, m, start_node;
 cout << "Enter no. of Nodes, no. of Edges, and Starting Node of the graph:\n";
 cin >> n >> m >> start_node;
 
 cout << "Enter pairs of nodes representing edges:\n";
 for (int i = 0; i < m; i++) {
 int u, v;
 cin >> u >> v;
 graph[u].push_back(v);
 graph[v].push_back(u);
 }
 // Initialize visited array
 for (int i = 0; i < n; i++) {
 visited[i] = false;
 }
 // Perform DFS from the start node
 dfs(start_node);
 
 return 0;
}
