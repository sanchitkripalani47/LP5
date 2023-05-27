#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge(int *arr, int start, int mid, int end) {
    int temp[end - start + 1];
    int i = start; // starting index for left subarray
    int j = mid + 1; // starting index for right subarray
    int k = 0; // starting index for temporary array

    while(i <= mid && j <= end) {
        if(arr[i] <= arr[j]) 
            temp[k++] = arr[i++];
        else    
            temp[k++] = arr[j++];
    }

    while(i <= mid) {
        temp[k++] = arr[i++];
    }
    while(j <= end) {
        temp[k++] = arr[j++];
    }

    for(i=start; i<=end; i++){
        arr[i] = temp[i-start];
    }
}

void serialMergeSort(int *arr, int start, int end){
    if(start < end){
        int mid = (start + end) / 2;
        serialMergeSort(arr, start, mid);
        serialMergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

void parallelMergeSort(int *arr, int start, int end) {
    if(start < end) {
        int mid = (start + end) / 2;
        #pragma omp parallel selections
        {
            #pragma omp selection
                parallelMergeSort(arr, start, mid);
            #pragma omp selection
                parallelMergeSort(arr, mid+1, end);
        }
        merge(arr, start, mid, end);
    }
}

int main(){
    int n = 5;
    int arr1[n] = {5, 4, 3, 1, 2};
    int arr2[n] = {5, 4, 3, 1, 2};

    // double start_time = omp_get_wtime();
    serialMergeSort(arr1, 0, n);
    // double end_time = omp_get_wtime();
    // cout << "Serial Merge Sort Time: " << end_time - start_time << endl;

    for(int i=0; i<n; i++){
        cout << arr1[i] << " ";
    }
    cout << endl;

    // start_time = omp_get_wtime();
    parallelMergeSort(arr2, 0, n);
    // end_time = omp_get_wtime();
    // cout << "Parallel Merge Sort Time: " << end_time - start_time << endl;

    for(int i=0; i<n; i++){
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}


/*
Serial Merge Sort Time: 1.115e-06
1 2 3 4 5 
Parallel Merge Sort Time: 1.021e-06
1 2 3 4 5
*/