#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
  public:
    vector<int> keys;
    vector<Node*> children;
    bool leaf;

    Node(bool leaf = false) {
      this->leaf = leaf;
    }
};

class BTree {
  private:
    Node* root;
    int t;

  public:
    BTree(int t) {
      this->t = t;
      root = new Node(true);
    }

    pair<Node*, int> search(int key, Node* node = nullptr) {
      if (node == nullptr) {
        node = root;
      }
      int i = 0;
      while (i < node->keys.size() && key > node->keys[i]) {
        i++;
      }
      if (i < node->keys.size() && key == node->keys[i]) {
        return make_pair(node, i);
      } else if (node->leaf) {
        return make_pair(nullptr, -1);
      } else {
        return search(key, node->children[i]);
      }
    }

    void splitChild(Node* node, int i) {
      Node* y = node->children[i];
      Node* z = new Node(y->leaf);

      node->children.insert(node->children.begin() + i + 1, z);
      node->keys.insert(node->keys.begin() + 1, y->keys[this->t - 1]);

      vector<int> newYKeys(y->keys.begin(), y->keys.begin() + t - 1);
      y->keys = newYKeys;
      vector<int> newZKeys(y->keys.begin() + t, y->keys.end());
      z->keys = newZKeys;

      if (!y->leaf) {
        vector<Node*> newYChildren(y->children.begin(), y->children.begin() + t - 1);
        y->children = newYChildren;
        vector<Node*> newZChildren(y->children.begin() + t, y->children.end());
        z->children = newZChildren;
      }
    }

    void insertNonFull(Node* node, int key) {
      int i = node->keys.size() - 1;
      if (node->leaf) {
        node->keys.push_back(-1);
        while (i >= 0 && node->keys[i] > key) {
          node->keys[i + 1] = node->keys[i];
        }
        node->keys[i + 1] = key;
      } else {
        while (i >= 0 && node->keys[i] > key) {
          i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * t - 1) {
          splitChild(node, i);
          if (node->keys[i] < key) {
            i++;
          }
        }
      }
      insertNonFull(node->children[i], key);
    }

    void insert(int key) {
      Node *root = this->root;
      if (root->keys.size() == 2 * t - 1) {
        Node *newRoot = new Node();
        this->root = newRoot;
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
      } else {
        insertNonFull(root, key);
      }
    }

    int deletePredecessor(Node *node) {
      if (node->leaf) {
          int key = node->keys[node->keys.size() - 1];
          node->keys.pop_back();
          return key;
      } else {
          int n = node->keys.size() - 1;
          if (node->children[n]->keys.size() >= t) {
            deleteSibling(node, n, n + 1);
          }
          return deletePredecessor(node->children[n]); 
      }
    }


    int deleteSuccessor(Node *node) {
      if (node->leaf) {
        int key = node->keys[0];
        node->keys.erase(node->keys.begin());
        return key;
      } else {
        if (node->children[1]->keys.size() >= t) {
          deleteSibling(node, 0, 1);
        }
        return deleteSuccessor(node->children[0]); 
      }
    }


    void deleteInternalNode(Node *node, int key, int i) {
      if (node->leaf) {
        if (node->keys[i] == key) {
          node->keys.erase(node->keys.begin() + i);
        }
        return;
      }

      if (node->children[i]->keys.size() >= t) {
        node->keys[i] = deletePredecessor(node->children[i]);
        return;
      } else if (node->children[i + 1]->keys.size() >= t) {
        node->keys[i] = deleteSuccessor(node->children[i + 1]);
        return;
      } else {
        deleteMerge(node, i, i + 1);
        deleteInternalNode(node->children[i], key, this->t - 1);
      }
    }

    void deleteSibling(Node *node, int i, int j) {
      Node *cnode = node->children[i];
      if (i < j) {
        Node *rsnode = node->children[j];
        cnode->keys.push_back(node->keys[i]);
        node->keys[i] = rsnode->keys[0];
        if (!rsnode->leaf) {
          cnode->children.push_back(rsnode->children[0]);
          rsnode->children.erase(rsnode->children.begin());
        }
        rsnode->keys.erase(rsnode->keys.begin());
      } else {
        Node *lsnode = node->children[j];
        cnode->keys.insert(cnode->keys.begin(), node->keys[i - 1]);
        node->keys[i - 1] = lsnode->keys[lsnode->keys.size() - 1];
        if (!lsnode->leaf) {
          cnode->children.insert(cnode->children.begin(), lsnode->children[lsnode->children.size() - 1]);
          lsnode->children.erase(lsnode->children.end() - 1);
        }
        lsnode->keys.erase(lsnode->keys.end() - 1);
      }
    }

    void deleteMerge(Node *node, int i, int j) {
      Node *cnode = node->children[i];
      Node *temp;

      if (i < j) {
        Node *rsnode = node->children[j];
        for (int k = 0; k < rsnode->keys.size(); k++) {
          cnode->keys.push_back(rsnode->keys[k]);
          if (rsnode->children.size() > 0) {
            cnode->children.push_back(rsnode->children[k]);          
          }
        }
        if (rsnode->children.size() > 0) {
          cnode->children.push_back(rsnode->children[rsnode->children.size() - 1]);
          rsnode->children.erase(rsnode->children.end() - 1);
        }
        temp = cnode;
        node->children.erase(node->children.begin() + j);
        node->keys.erase(node->keys.begin() + i);
      } else {
        Node *lsnode = node->children[j];
        lsnode->keys.push_back(node->keys[j]);
        for (int i = 0; i < cnode->keys.size(); i++) {
          lsnode->keys.push_back(cnode->keys[i]);
          if (cnode->children.size() > 0) {
            lsnode->children.push_back(cnode->children[i]);
          }
        }
        if (cnode->children.size() > 0) {
          lsnode->children.push_back(cnode->children[cnode->children.size() - 1]);
          cnode->children.erase(cnode->children.end() - 1);
        }
        temp = lsnode;
        node->children.erase(node->children.begin() + i);
        node->keys.erase(node->keys.begin() + i);
      }

      if (node == this->root && node->keys.size() == 0) {
        this->root = temp;
      }
    }

    void deleteKey(int key, Node *node = nullptr) {
      int i = 0;
      if (node == nullptr) {
        node = root;
      }
      while (i < node->keys.size() && key > node->keys[i]) {
        i++;
      }
      if (node->leaf) {
        if (i < node->keys.size() && key == node->keys[i]) {
          node->keys.erase(node->keys.begin() + i);
        }
        return;
      }

      if (i < node->keys.size() && node->keys[i] == key) {
        return deleteInternalNode(node, key, i);
      } else if (node->children[i]->keys.size() >= t) {
        deleteKey(key, node->children[i]);
      } else {
        if (i != 0 && i + 2 < node->children.size()) {
          if (node->children[i - 1]->keys.size() >= t) {
            deleteSibling(node, i, i - 1);
          } else if (node->children[i + 1]->keys.size() >= t) {
            deleteSibling(node, i, i + 1);
          } else {
            deleteMerge(node, i, i + 1);
          }
        } else if (i == 0) {
          if (node->children[i + 1]->keys.size() >= t) {
            deleteSibling(node, i, i + 1);
          } else {
            deleteMerge(node, i, i + 1);
          }
        } else if (i + 1 == node->children.size()) {
          if (node->children[i - 1]->keys.size() >= t) {
            deleteSibling(node, i, i - 1);
          } else {
            deleteMerge(node, i, i - 1);
          }
        }
        deleteKey(key, node->children[i]);
      }
    }

    void printTree(Node *node = nullptr, int level = 0) {
      if (node == nullptr) {
        node = root;
      }
      for (int i = 0; i < node->keys.size(); i++) {
        cout << node->keys[i] << " ";
      }
      cout << endl;
      if (!node->leaf) {
        for (int i = 0; i < node->children.size(); i++) {
          printTree(node->children[i], level + 1);
        }
      }

    }
};

void testSearch(BTree &t, int key) {
    pair<Node*, int> result = t.search(key);
    if (result.first != nullptr) {
        cout << "Key " << key << " found in node at position " << result.second << endl;
    } else {
        cout << "Key " << key << " not found in the tree." << endl;
    }
}

int main() {
  BTree t(3); 
  // insertions
  t.insert(10);
  t.printTree();
  t.insert(20);
  t.printTree();
  t.insert(5);
  t.printTree();
  t.insert(6);
  t.printTree();
  t.insert(12);
  t.printTree();
  t.insert(30);
  t.printTree();
  t.insert(7);
  t.printTree();
  t.insert(17);
  t.printTree();

  // searching
  testSearch(t, 6);
  testSearch(t, 15); // Should be not found

  // deletions
  t.deleteKey(6);
  t.printTree();
  t.deleteKey(13); // Key not present
  t.printTree();
  t.deleteKey(7);
  t.printTree();
  t.deleteKey(4); // Key not present
  t.printTree();
  t.deleteKey(2); // Key not present
  t.printTree();

  return 0;
}