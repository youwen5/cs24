// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"
#include <iostream>

using namespace std;

bool CardList::insert(Card &c) {
  if (root == nullptr) {
    root = new Node(c);
    return true;
  }
  return insert(c, root);
}

bool CardList::insert(Card &c, Node *n) {
  if (c == n->val) {
    return false;
  }
  if (c > n->val) {
    if (n->right == nullptr) {
      n->right = new Node(c);
      return true;
    }
    return insert(c, n->right);
  }
  if (c < n->val) {
    if (n->left == nullptr) {
      n->left = new Node(c);
      return true;
    }
    return insert(c, n->left);
  }
  return false;
}

void CardList::printDeck() const { printDeck(root); }

// in-order traversal
void CardList::printDeck(Node *n) const {
  if (n == nullptr)
    return;

  printDeck(n->left);

  cout << n->val << endl;

  printDeck(n->right);
}

bool CardList::contains(Card &c) const { return contains(c, root); }

bool CardList::contains(Card &c, Node *n) const {
  if (n == nullptr)
    return false;
  if (n->val == c) {
    return true;
  }
  if (c > n->val) {
    return contains(c, n->right);
  }
  return contains(c, n->left);
}
