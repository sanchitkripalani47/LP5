// Implement Min, Max, Sum and Average operations using Parallel Reduction.

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void get_min(int arr[], int n){
    int minEle = INT_MAX;
    double start_time = omp_get_wtime();
    for(int i=0; i<n; i++){
        minEle = min(minEle, arr[i]);
    }
    double end_time = omp_get_wtime();
    cout << "serial min: " << end_time - start_time << endl;
    cout << "min: " << minEle << endl;

    minEle = INT_MAX;
    start_time = omp_get_wtime();

    #pragma omp paralle for reduction(min : minEle)
        for(int i=0; i<n; i++){
            minEle = min(minEle, arr[i]);
        }
        
    end_time = omp_get_wtime();
    cout << "parallel min: " << end_time - start_time << endl;
    cout << "min: " << minEle << endl;
    
}

void get_max(int arr[], int n){
    int maxEle = INT_MIN;
    double start_time = omp_get_wtime();
    for(int i=0; i<n; i++){
        maxEle = max(maxEle, arr[i]);
    }
    double end_time = omp_get_wtime();
    cout << "serial max: " << end_time-start_time << endl;
    cout << maxEle << endl;

    start_time = omp_get_wtime();
    #pragma omp for reduction(max: maxEle)
    for(int i=0; i<n; i++){
        maxEle = max(maxEle, arr[i]);
    }
    end_time = omp_get_wtime();
    cout << "parallel max: " << end_time - start_time << endl;
    cout << "max:" << maxEle << endl; 
}

void get_sum(int arr[], int n){
    #pragma omp parallel for reduction(+: sum)
}

void get_avg(int arr[], int n){
    #pragma omp parallel for reduction(+: avg)
}

int main(){
    int n = 5;
    int arr[5] = {3, 4, 1, 5, 2};

    get_min(arr, n);
    get_max(arr, n);
    get_sum(arr, n);
    get_avg(arr, n);
}


/*
serial min: 3.21998e-07
min: 1
parallel min: 2.58999e-07
min: 1
serial max: 1.82998e-07
5
parallel max: 1.3e-07
max:5
*/