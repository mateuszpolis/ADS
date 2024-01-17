#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void selectionSort(vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    int max = 0;
    for (int j = 1; j < v.size() - i; j++) {
      if (v[j] > v[max]) {
        max = j;
      }
    }
    swap(v[max], v[v.size() - i - 1]); 
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
  selectionSort(array);
  print(array);
}