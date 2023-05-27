#include<iostream>
using namespace std;

void merge(int arr[], int start, int mid, int end) {
    int temp[end-start+1];
    int k = 0;
    int i = start;
    int j = mid+1;

    while(i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            k++;
            i++;
        }
        else {
            temp[k] = arr[j];
            k++;
            j++;
        }
    }

    while(i <= mid) {
        temp[k] = arr[i];
        k++;
        i++;
    }


    while(j <= end) {
        temp[k] = arr[j];
        k++;
        j++;
    }

    for (int i=start; i<=end; i++) {
        arr[i] = temp[i-start];
    }


}

void serialMerge(int arr[], int start, int end) {
    if (start < end) {
        int mid = (start+end)/2;
        serialMerge(arr, start, mid);
        serialMerge(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

void paraMerge(int arr[], int start, int end) {
    if (start < end) {
        int mid = (start+end)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            paraMerge(arr, start, mid);

            #pragma omp section
            paraMerge(arr, mid+1, end);
        }
        merge(arr, start, mid, end);

    }
}


int main() {

    int n = 5;
    int arr1[5] = {4,3,2,1,5};
    int arr2[5] = {4,3,2,1,5};

    serialMerge(arr1, 0, n);

    cout << "Sorting using serial merge sort: ";
    for (auto it: arr1) {
        cout << it << " ";
    }
    cout << "\n";

    paraMerge(arr2, 0, n);

    cout << "Sorting using parallel merge sort: ";
    for (auto it: arr2) {
        cout << it << " ";
    }
    cout << "\n";



    return 0;
}