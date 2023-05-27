#include<iostream>
#include<vector>

using namespace std;

void serialDFSUtil(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &ans, int n, int curr) {
    visited[curr] = true;
    ans.push_back(curr);

    for (auto v: graph[curr]) {
        if (!visited[v]) {
            serialDFSUtil(graph, visited, ans, n, v);
        }
    }

}

vector<int> serialDFS(vector<vector<int>> &graph, int n) {
    vector<bool> visited(n, false);
    vector<int> ans;

    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            serialDFSUtil(graph, visited, ans, n, i);
        }
    }

    return ans;
}

void paraDFSUtil(vector<vector<int>> graph, vector<bool> visited, vector<int> ans, int n, int i) {
    ans.push_back(i);
    visited[i] = true;

    #pragma omp parallel for
    for (auto v: graph[i]) {
        #pragma omp critical
        if (!visited[v]) {
            paraDFSUtil(graph, visited, ans, n, v);
        }
    }

}

vector<int> paraDFS(vector<vector<int>> &graph, int n) {
    vector<bool> visited(n, false);
    vector<int> ans;

    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            paraDFSUtil(graph, visited, ans, n, i);
        }
    }

    return ans;

}


int main() {

    int n = 5;
    vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{2,3},{3,4}};

    int u, v;
    vector<vector<int>> graph(n);

    for (auto it: edges) {
        u = it.first;
        v = it.second;
        graph[u].push_back(v);
    }

    cout << "Serial DFS: ";
    vector<int> ans_series = serialDFS(graph, n);
    for (auto it: ans_series) {
        cout << it << " ";
    }
    cout << "\n";

    cout << "Parallel DFS: ";
    vector<int> ans_para = paraDFS(graph, n);
    for (auto it: ans_para) {
        cout << it << " ";
    }
    cout << "\n";


    return  0;
}