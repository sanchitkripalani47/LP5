#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void serialBubbleSort(vector<int> arr, int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<arr.size()-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    cout << "serialBubbleSort: ";
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout << endl;
}

void parallelBubbleSort(vector<int> arr, int n){
    #pragma omp parallel
    {
        for(int i=0; i<arr.size(); i++){
            #pragma omp for
            for(int j=0; j<arr.size()-i-1; j++) {
                if(arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }
    cout << "parallelBubbleSort: ";
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << " "; 
    }
    cout << endl;
}

int main() {
    int n = 5;
    vector<int> arr = {4, 2, 5, 3, 1};

    // double start_time  = omp_get_wtime();
    serialBubbleSort(arr, n);
    // double end_time = omp_get_wtime();
    // double elapsed_time = end_time - start_time;
    // cout << "serialBubbleSort time: " << elapsed_time << endl;

    // start_time = omp_get_wtime();
    parallelBubbleSort(arr, n);
    // end_time = omp_get_wtime();
    // elapsed_time = end_time - start_time;
    // cout << "parallelBubbleSort time: " << elapsed_time << endl;
}

/*
serialBubbleSort: 1 2 3 4 5 
serialBubbleSort time: 8.8784e-05
parallelBubbleSort: 1 2 3 4 5 
parallelBubbleSort time: 2.5267e-05
*/