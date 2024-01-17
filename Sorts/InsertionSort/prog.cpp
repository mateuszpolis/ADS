#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& v) {
  for (int i = 1; i < v.size(); i++) {
    int j = i;
    while (j > 0 && v[j] < v[j - 1]) {
      swap(v[j], v[j - 1]);
      j--;
    }
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
  insertionSort(array);
  print(array);
}