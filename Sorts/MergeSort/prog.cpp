#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> &a, vector<int> &b) {
  vector<int> result;
  int i = 0, j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i] < b[j]) {
      result.push_back(a[i]);
      i++;
    } else {
      result.push_back(b[j]);
      j++;
    }
  }
  while (i < a.size()) {
    result.push_back(a[i]);
    i++;
  }
  while (j < b.size()) {
    result.push_back(b[j]);
    j++;
  }

  return result;
}

vector<int> mergeSort(vector<int>& v) {
  if (v.size() == 1) {
    return v;
  }

  vector<int> v1(v.begin(), v.begin() + v.size() / 2);
  vector<int> v2(v.begin() + v.size() / 2, v.end());

  v1 = mergeSort(v1);
  v2 = mergeSort(v2);

  return merge(v1, v2);
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
  array = mergeSort(array);
  print(array);
}