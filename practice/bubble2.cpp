#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

void serialBubble(vector<int> &arr) {
    int n = arr.size();

    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }

}

void paraBubble(vector<int> &arr) {
    int n = arr.size();
    #pragma omp parallel
    for (int i=0; i<n-1; i++) {
        #pragma omp for
        for (int j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


int main() {

    vector<int> arr1 = {4, 3, 1, 2, 5};
    vector<int> arr2 = {4, 3, 1, 2, 5};

    serialBubble(arr1);

    cout << "For Serial Bubble sort: ";
    for (auto it: arr1) {
        cout << it << " ";
    }
    cout << "\n";



    paraBubble(arr2);
    cout << "For Parallel Bubble sort: ";
    for (auto it: arr2) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}