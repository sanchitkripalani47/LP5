#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

vector<int> serialBfs(vector<vector<int>> graph, int n, int start){
    vector<int>ans;
    queue<int> q;
    q.push(start);
    vector<bool> visited(n, false);
    visited[start] = true;

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        ans.push_back(curr);

        for(auto adj : graph[curr]) {
            if(!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
        }
    }
    return ans;
}

vector<int> parallelBfs(vector<vector<int> > graph, int n, int start) {
    queue<int> q;
    q.push(start);
    vector<bool> visited(n, false);
    visited[start] = true;

    vector<int> ans;

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        ans.push_back(curr);

        #pragma omp parallel for
        for(auto adj : graph[curr]) {
            if(!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
        }
    }
    return ans;
}

int main(){
    int n = 5, m = 5;
   
    vector<vector<int> > graph(n);
    vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{2,3},{3,4}};
    int u, v;
    for(int i = 0; i <m; i++){
        u = edges[i].first;
        v = edges[i].second;
        graph[u].push_back(v);// cin >> u >> v;
    }

    double start_time = omp_get_wtime();
    vector<int> ans1 = serialBfs(graph, n, 0);
    double end_time = omp_get_wtime();

    double elapsed_time = end_time - start_time;
    cout << "Elapsed time for serial BFS: " << elapsed_time << " seconds" << endl;

    start_time = omp_get_wtime();
    vector<int> ans2 = parallelBfs(graph, n, 0);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    cout << "Elapsed time for parallel BFS: " << elapsed_time << " seconds" << endl;
}