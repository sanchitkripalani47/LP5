#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

vector<int> serialBFS(vector<vector<int>> graph, int n, int start) {
    queue<int> q1;
    vector<int> ans;

    vector<bool> visited(n, false);

    q1.push(start);

    visited[start] = true;

    while(!q1.empty()) {
        int curr = q1.front();
        q1.pop();
        ans.push_back(curr);

        for (auto it: graph[curr]) {
            if (!visited[it]) {
                q1.push(it);
                visited[it] = true;
            }
            
        }
    }

    return ans;
}

vector<int> paraBFS(vector<vector<int>> graph, int n, int start) {
    queue<int> q1;
    vector<int> ans;

    vector<bool> visited(n, false);

    q1.push(start);

    visited[start] = true;


    while(!q1.empty()) {
        int curr = q1.front();
        q1.pop();
        ans.push_back(curr);

        #pragma omp parallel for
        for (auto it: graph[curr]) {
            if (!visited[it]) {
                visited[it] = true;
                q1.push(it);
            }
        }

    }

    return ans; 
}


int main() {

    int n = 5;
    // creating edges first
    vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{2,3},{3,4}};

    // using adjacency matrix representation
    vector<vector<int>> graph(n);
    int u, v;
    for (auto it: edges) {
        u = it.first;
        v = it.second;
        graph[u].push_back(v);
    }

    double start = omp_get_wtime();
    vector<int> ans = serialBFS(graph, n, 0);
    double end = omp_get_wtime();
    cout << "Serial BFS: ";
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << "\n";
    double elapsed_time = end - start;
    cout << "Elapsed time for serial BFS: " << elapsed_time << " seconds" << endl;

    vector<int> paraAns = paraBFS(graph, n, 0);

    cout << "Parallel BFS: ";
    for (auto it: paraAns) {
        cout << it << " ";
    }
    cout << "\n";


    return 0;
}