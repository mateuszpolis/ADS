#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
  public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int key) {
      this->key = key;
      this->left = nullptr;
      this->right = nullptr;
      this->height = 1;
    }
};

class AVLTree {  // Adelson-Velsky and Landis
  public:
    Node *root;

    AVLTree() {
      root = nullptr;
    }

    AVLTree(int key) {
      root = new Node(key);
    }

    Node *search(int key, Node *node = nullptr) {
      if (node == nullptr) {
        node = root;
      }
      while (node != nullptr && key != node->key) {
        if (key < node->key) {
          node = node->left;
        } else {
          node = node->right;
        }
      }

      return node;
    }

    int getHeight(Node *node) {
      if (node == nullptr) {
        return 0;
      }
      return node->height;
    }

    int getBalanceFactor(Node *node) {
      if (node == nullptr) {
        return 0;
      }
      return getHeight(node->left) - getHeight(node->right);
    }

    Node *rotateLeft(Node *node) {
      Node *right = node->right;
      node->right = right->left;
      right->left = node;
      node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
      right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

      return right;
    }

    Node *rotateRight(Node *node) {
      Node *left = node->left;
      node->left = left->right;
      left->right = node;
      node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
      left->height = max(getHeight(left->left), getHeight(left->right)) + 1;

      return left;
    }

    Node *insert(Node *node, int key) {
      if (node == nullptr) {
        return new Node(key);
      } else if (key < node->key) {
        node->left = insert(node->left, key);
      } else {
        node->right = insert(node->right, key);
      }

      node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

      int balanceFactor = getBalanceFactor(node);

      if (balanceFactor > 1 && key < node->left->key) {
        return rotateRight(node);
      }
      if (balanceFactor < -1 && key > node->right->key) {
        return rotateLeft(node);
      }
      if (balanceFactor > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
      }
      if (balanceFactor < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
      }

      return node;
    }

    void printTree(Node *node, int level = 0) {            
      if (node != nullptr) {
        printTree(node->right, level + 1);
        cout << endl;
        if (node == root) {
          cout << "Root -> ";
        }
        for (int i = 0; i < level && node != root; i++) {
          cout << "        ";
        }
        cout << node->key;
        printTree(node->left, level + 1);
      } else {
        cout << endl;      
      }
    }
};

int main() {
  cout << "AVL Tree" << endl;
  AVLTree *tree = new AVLTree(10);
  cout << "Printing" << endl;
  tree->printTree(tree->root);

  cout << endl << "Inserting 20" << endl;
  tree->insert(tree->root, 20);
  tree->printTree(tree->root);

  cout << endl << "Inserting 30" << endl;
  tree->insert(tree->root, 30);
  tree->printTree(tree->root);

  cout << endl << "Inserting 40" << endl;
  tree->insert(tree->root, 40);
  tree->printTree(tree->root);

  cout << endl << "Inserting 50" << endl;
  tree->insert(tree->root, 50);
  tree->printTree(tree->root);

  cout << endl << "Inserting 25" << endl;
  tree->insert(tree->root, 25);
  tree->printTree(tree->root);

  return 0;
}