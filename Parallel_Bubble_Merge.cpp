#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;

void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n-i-1; j+=2) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }

        #pragma omp parallel for
        for (int j = 1; j < n-i-1; j+=2) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void merge(int *arr, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int *arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

int main() {
    int n = 10;
    int *arr = new int[n];
    int *copy = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
        copy[i] = arr[i];
    }

    
    
    
    // int n;
    // cout << "Enter the total number of elements: ";
    // cin >> n;

    // int *arr = new int[n];
    // int *copy = new int[n];

    // cout << "Enter the elements: ";
    // for (int i = 0; i < n; i++) {
    //     cin >> arr[i];
    //     copy[i] = arr[i];
    // }


    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << copy[i] << " ";
    }
    


    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by sequential Bubble Sort: " << duration.count() << " microseconds" << endl;

    
    start = chrono::high_resolution_clock::now();
    parallelBubbleSort(copy, n);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by parallel Bubble Sort: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
        copy[i] = arr[i];
    }

    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n-1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by sequential Merge Sort: " << duration.count() << " microseconds" << endl;

    
    start = chrono::high_resolution_clock::now();
    parallelMergeSort(copy, 0, n-1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by parallel Merge Sort: " << duration.count() << " microseconds" << endl;

    delete[] arr;
    delete[] copy;

    return 0;
}

// Compile: g++ -fopenmp Parallel_Bubble_Merge.cpp -o Parallel_Bubble_Merge
// Run: ./Parallel_Bubble_Merge