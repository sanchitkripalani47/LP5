#include<iostream>
#include<limits.h>
#include<omp.h>
using namespace std;

void get_min(int arr[], int n) {
    int min_ans = INT_MAX;

    double start = omp_get_wtime();
    for (int i=0; i<n; i++) {
        min_ans = min(min_ans, arr[i]);
    }
    double end = omp_get_wtime();
    cout << "Time for serial minimum: " << end - start << "\n";

    min_ans = INT_MAX;
    start = omp_get_wtime();

    #pragma omp parallel for reduction(min:min_ans) 
    for (int i=0; i<n; i++) {
        min_ans = min(min_ans, arr[i]);
    }
    end = omp_get_wtime();
    cout << "Time for parallel minimum: " << end - start << "\n";


}

int main() {

    int n = 100000;
    int arr[n];
    for (int i=n-1; i>=0; i--){
        arr[i] = i;
    }

    get_min(arr, n);

    return 0;
}