#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& v, int exp) {
    vector<int> output(v.size(), 0);
    vector<int> count(10, 0);

    for (int i = 0; i < v.size(); i++) {
        count[(v[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }

    v = output;
}

void radixSort(vector<int>& v, int max) {   
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(v, exp);
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
    int max = INT_MIN;
    while (n-- > 0) {
        int x;    
        cin >> x;
        if (x > max) {
          max = x;
        }
        array.push_back(x);
    }
    print(array);
    radixSort(array, max);
    print(array);
}
