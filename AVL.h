#pragma once

#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <typename T> class AVLTree {

  struct NodeBT {
    T data;
    NodeBT *left;
    NodeBT *right;
    NodeBT(T data_, NodeBT *left_ = nullptr, NodeBT *right_ = nullptr)
        : data(data_), left(left_), right(right_) {}
  };
  NodeBT *root;

private:
  void insert(NodeBT *&node, T value);
  void remove(NodeBT *&node, T value);
  void print(NodeBT *node, int depth);
  T minValue(NodeBT *node);
  T maxValue(NodeBT *node);

  void inOrder(NodeBT *node, string &str);
  void postOrder(NodeBT *node, string &str);
  void preOrder(NodeBT *node, string &str);
  T successor(NodeBT *node, T value, NodeBT *lastnode);
  T predecessor(NodeBT *node, T value, NodeBT *lastnode);

  int height(NodeBT *node) {
    if (node == nullptr) {
      return -1;
    } else {
      return 1 + max(height(node->right), height(node->left));
    }
  }

  int hb(NodeBT *node) { return height(node->left) - height(node->right); }

  void L_Rota(NodeBT *&node) {
    auto temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node = temp;
  }

  void R_Rota(NodeBT *&node) {
    auto temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node = temp;
  }

  void LR_Rota(NodeBT *&node) {
    R_Rota(node->left);
    L_Rota(node);
  }

  void RL_Rota(NodeBT *node) {
    R_Rota(node->right);
    L_Rota(node);
  }

  void Balancear(NodeBT *&node) {
    if (hb(node) >= 2) {
      if (hb(node->left) >= 0) {
        R_Rota(node);
      } else {
        LR_Rota(node);
      }
    }

    if (hb(node) <= -2) {
      if (hb(node->right) <= 0) {
        L_Rota(node);
      } else {
        RL_Rota(node);
      }
    }
  }

public:
  AVLTree() { root = nullptr; }
  void insert(T value);
  void remove(T value);
  void print();
  string inOrder();
  string postOrder();
  string preOrder();
  T minValue();
  T maxValue();
  T successor(T value);
  T predecessor(T value);
  void BreadthFirstSearch();
  void DepthFirstSearch();
};template <typename T>
void AVLTree<T>::BreadthFirstSearch() {
  queue<NodeBT *> cola;
  cout << "Recorrido por anchura" << endl;
  cola.push(this->root);

  while (!cola.empty()) {
    NodeBT *node = cola.front();
    cola.pop();
    cout << node->data << " ";
    if (node->left != nullptr)
      cola.push(node->left);
    if (node->right != nullptr)
      cola.push(node->right);
  }
  cout << endl;
}

template <typename T>
void AVLTree<T>::DepthFirstSearch() {
  cout << "Recorrido por profundidad" << endl;
  stack<NodeBT *> pila;
  pila.push(this->root);

  while (!pila.empty()) {
    NodeBT *node = pila.top();
    pila.pop();
    cout << node->data << " ";
    if (node->right != nullptr) {
      pila.push(node->right);
    }
    if (node->left != nullptr) {
      pila.push(node->left);
    }
  }
  cout << endl;
}

template <typename T>
T AVLTree<T>::successor(NodeBT *node, T value, NodeBT *lastnode) {
  if (node == nullptr) {
    if (lastnode) {
      return lastnode->data;
    } else {
      throw "no predecessor";
    }
  } else if (node->data < value) {
    return successor(node->right, value, lastnode);
  } else if (node->data > value) {
    lastnode = node;
    return successor(node->left, value, lastnode);
  } else {
    if (node->right) {
      return minValue(node->right);
    } else {
      return successor(node->right, value, lastnode);
    }
  }
}

template <typename T>
T AVLTree<T>::predecessor(NodeBT *node, T value, NodeBT *lastnode) {
  if (node == nullptr) {
    if (lastnode) {
      return lastnode->data;
    } else {
      throw "no predecessor";
    }
  } else if (node->data < value) {
    lastnode = node;

    return predecessor(node->right, value, lastnode);
  } else if (node->data > value) {

    return predecessor(node->left, value, lastnode);
  } else {
    if (node->left) {
      return maxValue(node->left);
    } else {
      return predecessor(node->left, value, lastnode);
    }
  }
}

template <typename T> T AVLTree<T>::successor(T value) {
  return successor(this->root, value, root->right);
}
template <typename T> T AVLTree<T>::predecessor(T value) {
  return predecessor(this->root, value, root->left);
}

template <typename T> string AVLTree<T>::preOrder() {
  string result = "";
  preOrder(root, result);
  return result;
}

template <typename T> void AVLTree<T>::preOrder(NodeBT *node, string &str) {
  if (!node) {
    return;
  }

  str += to_string(node->data);
  str += " ";

  preOrder(node->left, str);

  preOrder(node->right, str);
}
template <typename T> string AVLTree<T>::inOrder() {
  string result = "";
  inOrder(root, result);
  return result;
}

template <typename T> void AVLTree<T>::inOrder(NodeBT *node, string &str) {
  if (!node) {
    return;
  }
  inOrder(node->left, str);
  str += to_string(node->data);
  str += " ";
  inOrder(node->right, str);
}

template <typename T> string AVLTree<T>::postOrder() {
  string result = "";
  postOrder(root, result);
  return result;
}

template <typename T> void AVLTree<T>::postOrder(NodeBT *node, string &str) {
  if (!node) {
    return;
  }

  postOrder(node->left, str);
  postOrder(node->right, str);
  str += to_string(node->data);
  str += " ";
}

template <typename T> void AVLTree<T>::insert(T value) {
  insert(this->root, value);
}

template <typename T> void AVLTree<T>::insert(NodeBT *&node, T value) {
  if (node == nullptr) {
    node = new NodeBT(value);

  } else if (value < node->data) {
    insert(node->left, value);

  } else if (value > node->data) {
    insert(node->right, value);
  } else {
    return;
  }

  Balancear(node);
}

template <typename T> void AVLTree<T>::remove(T value) {
  remove(this->root, value);
}

template <typename T> T AVLTree<T>::minValue() { return minValue(root); }

template <typename T> T AVLTree<T>::maxValue() { return maxValue(root); }

template <typename T> T AVLTree<T>::minValue(NodeBT *node) {
  if (node == nullptr) {
    throw "vacio";
  } else if (node->left == nullptr) {
    return node->data;
  } else {
    return minValue(node->left);
  }
}

template <typename T> T AVLTree<T>::maxValue(NodeBT *node) {
  if (node == nullptr) {
    throw "vacio";
  } else if (node->right == nullptr) {
    return node->data;
  } else {
    return maxValue(node->right);
  }
}
template <typename T> void AVLTree<T>::remove(NodeBT *&node, T value) {
  if (node == nullptr) {
    return;
  } else if (value < node->data) {
    remove(node->left, value);
  } else if (value > node->data) {
    remove(node->right, value);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      NodeBT *temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp; 
        delete temp;
      }
    } else {

      T tempData = minValue(node->right);
      node->data = tempData;
      remove(node->right, tempData);
    }
  }
//  Balancear(node); 
}


template <typename T> void AVLTree<T>::print() { print(root, 0); }

template <typename T> void AVLTree<T>::print(NodeBT *node, int depth) {
  if (node) {
    print(node->right, depth + 1);
    for (int i = 0; i < depth; ++i) {
      cout << "    ";
    }
    cout << node->data << endl;

    print(node->left, depth + 1);
  }
}
