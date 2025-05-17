// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"
#include <iostream>

using namespace std;

bool CardList::insert(Card &c) {
  if (!root) {
    root = new Node(c);
    return true;
  }
  return insert(c, root);
}

bool CardList::insert(Card &c, Node *n) {
  if (c == n->val)
    return false;

  if (c < n->val) {
    if (n->left)
      return insert(c, n->left);
    n->left = new Node(c);
    n->left->parent = n;
    return true;
  } else {
    if (n->right)
      return insert(c, n->right);
    n->right = new Node(c);
    n->right->parent = n;
    return true;
  }
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
  if (!n)
    return false;
  if (c == n->val)
    return true;
  if (c < n->val)
    return contains(c, n->left);
  else
    return contains(c, n->right);
}

Node *CardList::findNode(const Card &key, Node *cur) const {
  while (cur) {
    if (key == cur->val)
      return cur;
    cur = (key < cur->val) ? cur->left : cur->right;
  }
  return nullptr;
}

Node *CardList::minNode(Node *sub) const {
  if (!sub)
    return nullptr;
  while (sub->left)
    sub = sub->left;
  return sub;
}

Node *CardList::maxNode(Node *sub) const {
  if (!sub)
    return nullptr;
  while (sub->right)
    sub = sub->right;
  return sub;
}

void CardList::transplant(Node *u, Node *v) {
  if (!u->parent) // u is root
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v)
    v->parent = u->parent;
}

void CardList::removeNodeWithLE1Child(Node *z) {
  Node *child = z->left ? z->left : z->right;
  transplant(z, child);
  delete z;
}

bool CardList::remove(Card &key) {
  Node *z = findNode(key, root);
  if (!z)
    return false;

  if (!z->left || !z->right) {
    removeNodeWithLE1Child(z);
  } else {
    Node *y = minNode(z->right);
    z->val = y->val;
    removeNodeWithLE1Child(y);
  }
  return true;
}

Node *CardList::getSuccessorNode(Node *x) const {
  if (!x)
    return nullptr;

  if (x->right) {
    Node *p = x->right;
    while (p->left)
      p = p->left;
    return p;
  }

  Node *p = x->parent;
  while (p && x == p->right) {
    x = p;
    p = p->parent;
  }
  return p;
}

Node *CardList::getPredecessorNode(Node *x) const {
  if (!x)
    return nullptr;

  if (x->left) {
    Node *p = x->left;
    while (p->right)
      p = p->right;
    return p;
  }

  Node *p = x->parent;
  while (p && x == p->left) {
    x = p;
    p = p->parent;
  }
  return p;
}

void CardList::iterator::advance() {
  if (cur) {
    cur = owner->getSuccessorNode(cur);
  } else {
    cur = owner->minNode(owner->root);
  }
}
void CardList::iterator::retreat() {
  if (cur) {
    cur = owner->getPredecessorNode(cur);
  } else {
    cur = owner->maxNode(owner->root);
  }
}

CardList::iterator CardList::iterator::operator++(int) {
  iterator tmp = *this;
  advance();
  return tmp;
}
CardList::iterator CardList::iterator::operator--(int) {
  iterator tmp = *this;
  retreat();
  return tmp;
}

CardList::iterator &CardList::iterator::operator++() {
  advance();
  return *this;
}

CardList::iterator &CardList::iterator::operator--() {
  retreat();
  return *this;
}

CardList::iterator CardList::begin() const {
  return iterator(minNode(root), this);
}
