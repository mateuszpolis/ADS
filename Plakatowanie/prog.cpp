#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

void solve (vector<int> towers) {
  stack<int> stack; 
  int count = 0;

  for (int h: towers) {
    while (!stack.empty() && stack.top() > h) {
      stack.pop();
    }

    if (stack.empty() || stack.top() < h) {
      stack.push(h);
      count++;
    }
  }
  cout << count;
}

int main() {
  int n;
  cin >> n;
  vector<int> towers;
  for (int i = 0; i < n; i++) {
    int w, h;
    cin >> w >> h;
    towers.push_back(h);
  }   
  solve(towers);
}