#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void serialDfsUtil(vector<vector<int>> &g, vector<int> &result, vector<bool> &visited, int u){
    visited[u] = true;
    result.push_back(u);

    for(int v: g[u]){
        if(!visited[v])
            serialDfsUtil(g, result, visited, v);
    }
}

void parallelDfsUtil(vector<vector<int>> &g, vector<bool> &visited, vector<int> result, int n, int u){
    visited[u] = true;
    result.push_back(u);

    
    #pragma omp parallel for
    for(int v: g[u]){
        // critical section, which will be executed one thread at a time
        #pragma omp critical
        {
            if(!visited[v])
                parallelDfsUtil(g, visited, result, n, v);
        }
    }
}


void serialDfs(vector<vector<int>> &g, int n){
    vector<bool> visited(n, false);
    vector<int> result;

    for(int i = 0; i < n; i++){
        if(!visited[i])
            serialDfsUtil(g, result, visited, i);
    }

    cout << "Serial DFS traversal: ";
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
}

void parallelDfs(vector<vector<int>> &g, int n){
    vector<bool> visited(n, false);
    vector<int> result;

    
    for(int i = 0; i < n; i++){
        if(!visited[i])
            parallelDfsUtil(g, visited, result, n, i);
    }

    cout << "Parallel DFS traversal: ";
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
}

int main() {
    int n = 5, m = 5;
   
    vector<vector<int> > graph(n);
    vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{2,3},{3,4}};
    int u, v;
    for(int i = 0; i <m; i++){
        u = edges[i].first;
        v = edges[i].second;
        graph[u].push_back(v);
    }

    // double start_time = omp_get_wtime();
    serialDfs(graph, n);
    // double end_time = omp_get_wtime();

    // double elapsed_time = end_time - start_time;
    // cout << "Elapsed time for serial BFS: " << elapsed_time << " seconds" << endl;

    // start_time = omp_get_wtime();
    parallelDfs(graph, n);
    // end_time = omp_get_wtime();
    // elapsed_time = end_time - start_time;
    // cout << "Elapsed time for parallel BFS: " << elapsed_time << " seconds" << endl;
}

/*
Serial DFS traversal: 0 1 3 4 2 
Elapsed time for serial BFS: 4.0559e-05 seconds
Parallel DFS traversal: 
Elapsed time for parallel BFS: 8.73e-06 seconds
*/