#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 1; j < v.size(); j++) {
      if (v[j] < v[j - 1]) {
        swap(v[j], v[j - 1]);
      }
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
  bubbleSort(array);
  print(array);
}