#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

vector<int> serialBFS(vector<vector<int>> graph, int start, int n) {
    vector<int> ans;
    queue<int> q1;
    q1.push(start);
    vector<bool> visited(n, false);
    visited[start] = true;

    while(!q1.empty()) {
        int curr = q1.front();
        q1.pop();
        ans.push_back(curr);

        for (auto it: graph[curr]) {
            if (!visited[it]) {
                visited[it] = true;
                q1.push(it);
            }
        }
    }

    return ans;
}

vector<int> paraBFS(vector<vector<int>> graph, int start, int n) {
    vector<int> ans;
    queue<int> q1;
    q1.push(start);
    vector<bool> visited(n, false);
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

    vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{2,3},{3,4}};

    vector<vector<int>> graph(n);

    int u, v;

    for (auto it: edges) {
        u = it.first;
        v = it.second;
        graph[u].push_back(v);
    }

    double start = omp_get_wtime();
    vector<int> ans1 = serialBFS(graph, 0, n);
    double end = omp_get_wtime();
    cout << "Time serial: " << end-start << "\n";
    for (auto it: ans1) {
        cout << it << " ";
    }
    cout << "\n";

    double start_time = omp_get_wtime();
    vector<int> ans2 = paraBFS(graph, 0, n);
    double end_time = omp_get_wtime();
    cout << "Time para: " << end_time-end_time << "\n";
    for (auto it: ans2) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}