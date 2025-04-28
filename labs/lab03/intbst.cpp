// intbst.cpp
// Implements class IntBST
// Youwen Wu, 28 April 2025

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { root = nullptr; }

// destructor deletes all nodes
IntBST::~IntBST() { clear(root); }

// recursive helper for destructor
void IntBST::clear(Node *n) {
  if (n == nullptr)
    return;

  clear(n->left);
  clear(n->right);

  delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
  if (root == nullptr) {
    root = new Node(value);
    return true;
  }

  return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
  if (value < n->info) {
    if (n->left == nullptr) {
      n->left = new Node(value);
      n->left->parent = n;
      return true;
    }
    return insert(value, n->left);
  }
  if (value > n->info) {
    if (n->right == nullptr) {
      n->right = new Node(value);
      n->right->parent = n;
      return true;
    }
    return insert(value, n->right);
  }

  // trichotomy of ordered field
  return false;
}

// print tree data pre-order
void IntBST::printPreOrder() const { printPreOrder(root); }

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
  if (n == nullptr)
    return;

  cout << n->info << " ";
  printPreOrder(n->left);
  printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const { printInOrder(root); }
void IntBST::printInOrder(Node *n) const {
  if (n == nullptr)
    return;

  printInOrder(n->left);
  cout << n->info << " ";
  printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const { printPostOrder(root); }

void IntBST::printPostOrder(Node *n) const {
  if (n == nullptr)
    return;

  printPostOrder(n->left);
  printPostOrder(n->right);
  cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const { return sum(root); }

// recursive helper for sum
int IntBST::sum(Node *n) const {
  if (n == nullptr)
    return 0;

  return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const { return count(root); }

// recursive helper for count
int IntBST::count(Node *n) const {
  if (n == nullptr)
    return 0;

  return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none
// exists Parameters: int value: the value to be found Node* n: the node to
// start with (for a recursive call) Whenever you call this method from
// somewhere else, pass it the root node as "n"
IntBST::Node *IntBST::getNodeFor(int value, Node *n) const {
  if (n == nullptr)
    return NULL;

  if (value < n->info) {
    return getNodeFor(value, n->left);
  }

  if (value > n->info) {
    return getNodeFor(value, n->right);
  }

  return n;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
  return getNodeFor(value, root) != NULL;
}

// returns the Node containing the predecessor of the given value
IntBST::Node *IntBST::getPredecessorNode(int value) const {
  Node *ptrUp = getNodeFor(value, root);

  if (ptrUp == NULL)
    return NULL;

  Node *ptrDown = ptrUp->left;

  while (ptrUp != root) {
    if (ptrUp->info < value) {
      break;
    }
    ptrUp = ptrUp->parent;
  }

  while (ptrDown != nullptr) {
    if (ptrDown->info < value) {
      return ptrUp->info == value || ptrDown->info > ptrUp->info ? ptrDown
                                                                 : ptrUp;
    }
    if (ptrDown->right->info < value) {
      ptrDown = ptrDown->right;
    } else {
      ptrDown = ptrDown->left;
    }
  }

  if (ptrUp->info == value || ptrUp->info > value) {
    return NULL;
  }
  return ptrUp;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
  Node *node = getPredecessorNode(value);
  if (node == NULL)
    return 0;

  return node->info;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const {
  Node *ptrUp = getNodeFor(value, root);
  if (ptrUp == NULL)
    return NULL;

  Node *ptrDown = ptrUp->right;

  while (ptrUp != root) {
    if (ptrUp->info > value) {
      break;
    }
    ptrUp = ptrUp->parent;
  }

  while (ptrDown != nullptr) {
    if (ptrDown->info > value) {
      return ptrDown->info < ptrUp->info ? ptrDown : ptrUp;
    }
    if (ptrDown->left->info > value) {
      ptrDown = ptrDown->left;
    } else {
      ptrDown = ptrDown->right;
    }
  }

  return NULL;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
  Node *node = getSuccessorNode(value);
  if (node == NULL)
    return 0;

  return node->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not
// exist
bool IntBST::remove(int value) {
  return false; // REPLACE THIS NON-SOLUTION
}
