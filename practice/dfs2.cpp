#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

void serialDFSUtil(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &ans, int n, int curr) {
    visited[curr] = true;
    ans.push_back(curr);

    for (auto it: graph[curr]) {
        if (!visited[it]) {
            serialDFSUtil(graph, visited, ans, n, it);
        }
    }
}

vector<int> serialDFS(vector<vector<int>> graph, int n) {
    vector<int> ans;
    vector<bool> visited(n, false);

    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            serialDFSUtil(graph, visited, ans, n, i);
        }
    }

    return ans;
}

void paraDFSUtil(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &ans, int n, int curr) {
    visited[curr] = true;
    ans.push_back(curr);

    #pragma omp parallel for
    for (auto it: graph[curr]) {
        if (!visited[it]) {
            serialDFSUtil(graph, visited, ans, n, it);
        }
    }
}


vector<int> paraDFS(vector<vector<int>> graph, int n) {
    vector<int> ans;
    vector<bool> visited(n, false);

    #pragma omp parallel for
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            serialDFSUtil(graph, visited, ans, n, i);
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
    vector<int> ans = serialDFS(graph, n);
    double end = omp_get_wtime();
    cout << "time s: " << end-start << "\n";
    cout << "Serial DFS: ";
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << "\n";


    double start_time = omp_get_wtime();
    vector<int> ans2 = serialDFS(graph, n);
    double end_time = omp_get_wtime();
    cout << "time s: " << end_time-start_time << "\n";
    cout << "Para DFS: ";
    for (auto it: ans2) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}