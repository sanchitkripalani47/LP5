#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

void merge(vector<int> &arr, int start, int mid, int end) {
    int temp[end-start+1];

    int k = 0;
    int j = mid+1;
    int i = start;

    while(i<=mid && j<=end) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while(i<=mid) {
        temp[k] = arr[i];
        k++;
        i++; 
    }

    while(j<=end) {
        temp[k] = arr[j];
        k++;
        j++; 
    }

    for (i=start; i<=end; i++) {
        arr[i] = temp[i-start];
    }

}

void serialMerge(vector<int> &arr, int start, int end) {
    if (start < end) {
        int mid = (start+end)/2;
        serialMerge(arr, start, mid);
        serialMerge(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

int main() {

    int n = 5;
    vector<int> arr1 = {2,3,4,1,0};

    double start = omp_get_wtime();
    serialMerge(arr1, 0, n);
    double end = omp_get_wtime();
    cout << "time s: " << end-start << "\n";
    cout << "Serial DFS: ";
    for (auto it: arr1) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}