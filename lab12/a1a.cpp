#include <iostream>
using namespace std;

void Linear(int arr[], int n, int key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            cout << "Key " << key << " found at index: " << i << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Element not found" << endl;
    }
}

void Binary(int arr[], int n, int key) {
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] == key) {
            cout << "Key " << key << " found at index: " << mid << endl;
            return; // exit after finding
        } 
        else if (key < arr[mid]) {
            end = mid - 1;
        } 
        else {
            start = mid + 1;
        }
    }
    cout << "Element not found" << endl;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if (!flag) break; 
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[minIndex], arr[i]);
    }
}

int main() {
    int arr[] = {2, 3, 1, 6, 77, 8, 9, 23, 4, 0, 10, 11};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    // Searching
    Linear(arr, n, 29);
    Binary(arr2, n2, 11); // needs sorted array

    // Sorting
    bubbleSort(arr, n);
    cout << "Array after bubble sort: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    selectionSort(arr, n);
    cout << "Array after selection sort: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
