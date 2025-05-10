// intbst.cpp
// Implements class IntBST
// Youwen Wu, 28 April 2025

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { root = nullptr; }

// destructor deletes all nodes
IntBST::~IntBST() {
  clear(root);
  root = nullptr;
}

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
  Node *n = getNodeFor(value, root);

  Node *ptrDown = ptrUp->left;
  while (ptrUp->parent != nullptr && ptrUp->parent->info > value) {
    ptrUp = ptrUp->parent;
  }

  if (n->left) {
    Node *current = n->left;
    while (current->right) {
      current = current->right;
    }
    return current;
  }

  Node *current = n;
  Node *p = current->parent;

  while (p != nullptr && current == p->left) {
    current = p;
    p = p->parent;
  }
  return p;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
  Node *node = getPredecessorNode(value);
  if (node == nullptr)
    return 0;

  return node->info;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const {
  Node *currentNode = getNodeFor(value, root);

  if (!currentNode) {
    return nullptr;
  }

  if (currentNode->right) {
    Node *successorNode = currentNode->right;
    while (successorNode->left) {
      successorNode = successorNode->left;
    }
    return successorNode;
  }

  Node *parentNode = currentNode->parent;
  Node *childNode = currentNode;

  while (parentNode != nullptr && childNode == parentNode->right) {
    childNode = parentNode;
    parentNode = parentNode->parent;
  }

  return parentNode;
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
  Node *nodeToRemove = getNodeFor(value, root);

  if (!nodeToRemove) {
    return false;
  }

  Node *parent = nodeToRemove->parent;

  if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
    if (nodeToRemove == root) {
      root = nullptr;
    } else if (parent->left == nodeToRemove) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
    delete nodeToRemove;
    return true;
  } else if (nodeToRemove->left == nullptr || nodeToRemove->right == nullptr) {
    Node *child = (nodeToRemove->left != nullptr) ? nodeToRemove->left
                                                  : nodeToRemove->right;
    child->parent = parent;

    if (nodeToRemove == root) {
      root = child;
    } else if (parent->left == nodeToRemove) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    delete nodeToRemove;
    return true;
  }

  Node *successor = nodeToRemove->right;
  while (successor->left != nullptr) {
    successor = successor->left;
  }

  int successorValue = successor->info;
  nodeToRemove->info = successorValue;

  Node *successorParent = successor->parent;
  Node *successorChild = successor->right;

  if (successorChild != nullptr) {
    successorChild->parent = successorParent;
  }

  if (successorParent->left == successor) {
    successorParent->left = successorChild;
  } else {
    successorParent->right = successorChild;
  }

  delete successor;
  return true;
}
