#include <iostream>
#include <vector>

using namespace std;

int getPivot(vector<int> &v, int low, int high) {
    int mid = low + (high - low) / 2;
    if (v[low] < v[mid] < v[high] || v[high] < v[mid] < v[low]) {
        return mid;
    } else if (v[mid] < v[low] < v[high] || v[high] < v[low] < v[mid]) {
        return low;
    } else {
        return high;
    }
}

int partition(vector<int> &v, int low, int high) {
    int pivotIndex = getPivot(v, low, high);
    int pivotValue = v[pivotIndex];
    swap(v[pivotIndex], v[high]);
    int i = low;

    for (int j = low; j < high; j++) {
        if (v[j] <= pivotValue) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[high]);
    return i;
}

void quickSort(vector<int> &v, int low, int high) {
    if (low < high) {
        int pivotLocation = partition(v, low, high);
        quickSort(v, low, pivotLocation - 1);
        quickSort(v, pivotLocation + 1, high);
    }
}

void print(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    vector<int> array;
    cin >> n;
    while (n > 0) {
        int x;
        cin >> x;
        array.push_back(x);
        n--;
    }
    print(array);
    quickSort(array, 0, array.size() - 1);
    print(array);
}
