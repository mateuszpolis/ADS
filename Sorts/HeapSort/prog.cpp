#include <iostream>
#include <sstream>
#include <vector>
#include <climits> 
#include <cmath>
#include <iomanip> 

using namespace std;

class Heap {
  private:
    vector<int> heap;
    int heapSize;

    void maxHeapify(int i) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int largest = i;
      if (left < heapSize && heap[left] > heap[largest]) {
        largest = left;
      }
      if (right < heapSize && heap[right] > heap[largest]) {
        largest = right;
      }
      if (largest != i) {
        swap(heap[i], heap[largest]);
        maxHeapify(largest);
      }
    }

    void buildMaxHeap() {
      for (int i = heapSize / 2; i >= 0; i--) {
        maxHeapify(i);
      }
    }
  
  public:
    Heap(vector<int>& v) {
      heap = v;
      heapSize = v.size();
      buildMaxHeap();
    }

    void printHeap() {
      int depth = log2(heapSize) + 1; 
      int width = (pow(2, depth) - 1) * 2;

      int index = 0; 
      for (int level = 0; level < depth; level++) {
        int levelWidth = pow(2, level); 
        int space = width / (levelWidth + 1);

        for (int i = 0; i < levelWidth && index < heap.size(); i++, index++) {
            cout << setw(space) << heap[index] << setw(space) << ' ';
        }
        cout << endl;
      }
    }

    void printHeapArray() {
      for (int i = 0; i < heapSize; i++) {
        cout << heap[i] << " ";
      }
      cout << endl;
    }

    void heapSort() {
      int originalSize = heapSize;
      buildMaxHeap();
      for (int i = heap.size() - 1; i >= 1; i--) {
          swap(heap[0], heap[i]);
          heapSize--;
          maxHeapify(0);
      }
      heapSize = originalSize;
    }

};

int main() {
  int n;
  vector<int> array;
  cin >> n;
  while (n-- > 0) {
    int x;    
    cin >> x;
    array.push_back(x);
  }
  Heap heap(array);
  heap.printHeapArray();
  heap.heapSort();
  heap.printHeapArray();
}