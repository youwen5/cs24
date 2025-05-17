// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's
// hand

#ifndef __CARD_LIST_H__
#define __CARD_LIST_H__

#include "card.h"
#include <iterator>

class Node {
public:
  Card val;
  Node *left;
  Node *right;
  Node *parent;
  Node(const Card &v)
      : val(v), left(nullptr), right(nullptr), parent(nullptr) {};
};

class CardList {
public:
  class iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = Card;
    using pointer = Card *;
    using reference = Card &;
    iterator() : cur(nullptr), owner(nullptr) {}

    Card &operator*() const { return cur->val; }
    Card *operator->() const { return &cur->val; }

    iterator operator++(int);
    iterator operator--(int);
    iterator &operator++();
    iterator &operator--();

    bool operator==(const iterator &rhs) const { return cur == rhs.cur; }
    bool operator!=(const iterator &rhs) const { return cur != rhs.cur; }

  private:
    friend class CardList;
    iterator(Node *n, const CardList *o) : cur(n), owner(o) {}

    void advance();
    void retreat();

    Node *cur;
    const CardList *owner;
  };
  CardList() : root(nullptr) {};
  ~CardList() {
    clear(root);
    root = nullptr;
  }
  void clear(Node *n) {
    if (n == nullptr)
      return;

    clear(n->left);
    clear(n->right);

    delete n;
  }
  CardList(CardList &other) {
    if (other.root) {
      root = copy(other.root, nullptr);
    }
  }
  CardList &operator=(const CardList &other) {
    if (this == &other) {
      return *this;
    }
    clear(root);
    root = nullptr;
    if (other.root) {
      root = copy(other.root, nullptr);
    }
    return *this;
  }
  bool insert(Card &);
  bool contains(Card &) const;
  bool remove(Card &);
  void printDeck() const;
  Node *getPredecessorNode(Node *) const;
  Node *getSuccessorNode(Node *) const;
  Node *get_root() const { return root; }
  iterator begin() const;
  iterator end() const { return iterator(nullptr, this); }
  std::reverse_iterator<iterator> rbegin() {
    return std::reverse_iterator(end());
  }
  std::reverse_iterator<iterator> rend() {
    return std::reverse_iterator(begin());
  }

private:
  bool insert(Card &, Node *);
  Node *root;
  void printDeck(Node *) const;
  bool contains(Card &, Node *) const;
  Node *findNode(const Card &, Node *) const;
  void transplant(Node *u, Node *v);
  void removeNodeWithLE1Child(Node *z);
  Node *minNode(Node *) const;
  Node *maxNode(Node *) const;
  Node *copy(Node *source, Node *newParent) {
    if (!source) {
      return nullptr;
    }
    Node *newNode = new Node(source->val);
    newNode->parent = newParent;
    newNode->left = copy(source->left, newNode);
    newNode->right = copy(source->right, newNode);
    return newNode;
  }
};
#endif
