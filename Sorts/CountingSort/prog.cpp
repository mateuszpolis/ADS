#include <iostream>
#include <sstream>
#include <vector>
#include <climits> 

using namespace std;

void countingSort(vector<int>& v, int min, int max) {
  vector<int> frequencyArray(max - min + 1, 0); 
  for (int i = 0; i < v.size(); i++) {
    frequencyArray[v[i] - min]++;
  }
  for (int i = 1; i < frequencyArray.size(); i++) {
    frequencyArray[i] += frequencyArray[i - 1];
  }
  vector<int> result(v.size(), 0);
  for (int i = v.size() - 1; i >= 0; i--) {
    result[frequencyArray[v[i] - min] - 1] = v[i]; 
    frequencyArray[v[i] - min]--;
  }
  v = result;
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
  int min = INT_MAX, max = INT_MIN;
  while (n-- > 0) {
    int x;    
    cin >> x;
    min = std::min(min, x);
    max = std::max(max, x);
    array.push_back(x);
  }
  print(array);
  countingSort(array, min, max);
  print(array);
}
