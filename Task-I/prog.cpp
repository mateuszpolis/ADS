#include <iostream>
#include <vector>

using namespace std;

#define ID 0

class Party {
private:
  int id;
  int votes;
  int seats;

public:
  Party()
  {
    this->id = -1;
    this->votes = 0;
    this->seats = 0;
  }

  Party(int id, int votes) {
    this->id = id;
    this->votes = votes;
    this->seats = 0;
  }

  void AddSeat() { this->seats++; };
  int GetId() { return this->id; };
  bool operator>(const Party &other) 
  {
    if ((this->votes) * (other.seats + 1) > (other.votes) * (this->seats + 1)){
      return true;
    }
    else if ((this->votes) * (other.seats + 1) == (other.votes) * (this->seats + 1)){
      return this->id < other.id;
    }
    else{
      return false;
    }
  } 
};

class Heap {
private:
  vector<Party> elements;
  int size;

public:
  Heap(int n) {
    this->size = 0;
    this->elements = vector<Party>(n + 1);
  }

  void Add(Party p) {
    int index = ++size;
    elements[index] = p;
    while (true) {      
      if (index / 2 < 1) {
        break;
      }
      if (elements[index] > elements[index / 2]) {
        swap(elements[index / 2], elements[index]);
      } else {
        break;
      }
      index /= 2;
    }
  };

  Party *GetLeftChild(int index) {
    if (index * 2 > size) {
      return nullptr;
    }
    return &this->elements[index * 2];
  }

  Party *GetRightChild(int index) {
    if (index * 2 + 1 > size) {
      return nullptr;
    }
    return &this->elements[index * 2 + 1];
  }

  void DownHeap() {
    int index = 1;
    while (true) {
      Party *leftChild = GetLeftChild(index);
      Party *rightChild = GetRightChild(index);
      if (leftChild == nullptr && rightChild == nullptr) {
        break;
      }
      if (leftChild != nullptr && rightChild != nullptr && *leftChild > *rightChild && *leftChild > elements[index]) {
        swap(*leftChild, elements[index]);
        index = index * 2;
      } 
      else if (rightChild != nullptr && *rightChild > elements[index]) {
        swap(*rightChild, elements[index]);
        index = index * 2 + 1;
      } else {
        break;
      }
    }
  }
  Party *GetTop() { return &elements[1]; };
};

vector<int> calculateVotes(int parties, int seats, Heap &data) {
  vector<int> results(parties, 0);
  int seatsCurrent = 0;
  while (seatsCurrent < seats) {
    Party *top = data.GetTop();
    top->AddSeat();
    results[top->GetId()]++;
    data.DownHeap();
    seatsCurrent++;
  }

  return results;
}

void printResults(vector<int> results) {
  for (int i = 0; i < results.size(); i++) {
    cout << results[i] << " ";
  }
  cout << "\n";
}

int main() {
  int z;
  cin >> z;
  while (z > 0) {
    int n, s;
    cin >> n >> s;
    Heap data = Heap(n);
    for (int i = 0; i < n; i++) {
      int nOfVotes;
      cin >> nOfVotes;
      Party newParty = Party(i, nOfVotes);
      data.Add(newParty);
    }
    vector<int> results = calculateVotes(n, s, data);
    printResults(results);
    z--;
  }
}